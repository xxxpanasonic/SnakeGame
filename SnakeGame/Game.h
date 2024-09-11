#pragma once
#include <time.h>
#include <stdlib.h>
namespace SnakeGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;	
	/// <summary>
	/// Сводка для Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
	public:
		Game(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Game()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void OnPaint(System::Object^ obj, PaintEventArgs^ e) override {
			Graphics^ g = e->Graphics;
			
			Brush^ fruitBrush = gcnew SolidBrush(Color::DarkRed);
			g->FillRectangle(fruitBrush, fruitPosition.X, fruitPosition.Y, blockSize, blockSize);

			Brush^ snakeBrush = gcnew SolidBrush(Color::ForestGreen);
			for each(Point el in snake)
			g->FillRectangle(snakeBrush, el.X, el.Y, blockSize, blockSize);
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<Point>^ snake;
		Point fruitPosition;
		const int blockSize = 20;

		int fruitCount = 0;
		Label^ scoreLabel;
		Timer^ timer;
		int moveX = 1, moveY = 0;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(500, 500);
			this->Text = L"Snake Game by Olkhovik";
			this->BackColor = Color::Black;
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;


			scoreLabel = gcnew Label();
			scoreLabel->ForeColor = Color::White;
			scoreLabel->BackColor = Color::Transparent;
			scoreLabel->Text = "Счёт: 0";
			scoreLabel->Location = Point(10, 10);
			this->Controls->Add(scoreLabel);

			snake = gcnew List<Point>();
			snake->Add(Point(200,200));

			srand(time(NULL));
			PlaceFruit();

			timer = gcnew Timer();
			timer->Interval = 200;
			timer->Tick += gcnew EventHandler(this, &Game::OnTimerTick);
			timer->Start();


			this->Paint += gcnew PaintEventHandler(this, &Game::OnPaint);
			this->KeyDown += gcnew KeyEventHandler(this, &Game::OnKeyDown);
		}
		
		void PlaceFruit() {
			int maxX = this->ClientSize.Width / blockSize;
			int maxY = this->ClientSize.Height / blockSize;
			do {
			fruitPosition = Point(rand() % maxX *blockSize, 100);
			} while (snake->Contains(fruitPosition));
		}
		void OnTimerTick(Object^ obj, EventArgs^ e) {
			MoveSnake();
			if (snake[0].X < 0 || snake[0].Y < 0 || snake[0].X >= this->ClientSize.Width || snake[0].Y >= this->ClientSize.Height) {
				timer->Stop();
				MessageBox::Show("Ты проиграл :(");
				return;
			}
			if (snake->Count >= 4) {
				for (int i = 1; i < snake->Count; i++) {
					if (snake[0] == snake[i]) {
						timer->Stop();
						MessageBox::Show("Ты скушал сам себя :(");
						return;
					}
				}
			}


			if (snake[0] == fruitPosition) {
				fruitCount++;
				scoreLabel->Text = "Счёт: " + fruitCount.ToString();
				GrowthSnake();
				PlaceFruit();
			}
			if (fruitCount == 25) {
				timer->Stop();
				MessageBox::Show("Ты выиграл :)");
				return;
			}
			this->Invalidate();
		}
		void GrowthSnake() {
			Point newHead = snake[0];

			newHead.X += moveX * blockSize;
			newHead.Y += moveY * blockSize;
			snake->Insert(0, newHead);
			}

		void MoveSnake() {
			Point newHead = snake[0];

			newHead.X += moveX * blockSize;
			newHead.Y += moveY * blockSize;
			snake->Insert(0, newHead);
			snake->RemoveAt(snake->Count - 1);

			}
			 
		
		void OnKeyDown(Object^ obj, KeyEventArgs^ e) {
			switch (e->KeyCode) {
			case Keys::Up:
					moveX = 0;
					moveY = -1;
					break;
			case Keys::Down:
				moveX = 0;
				moveY = 1;
				break;
			case Keys::Left:
				moveX = -1;
				moveY = 0;
				break;
			case Keys::Right:
				moveX = 1;
				moveY = 0;
				break;

			}
		}
#pragma endregion
	};
}
