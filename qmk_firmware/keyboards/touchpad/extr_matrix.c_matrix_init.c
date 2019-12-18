#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  B4 ; 
 int /*<<< orphan*/  B5 ; 
 int /*<<< orphan*/  B6 ; 
 int /*<<< orphan*/  B7 ; 
 int /*<<< orphan*/  C6 ; 
 int /*<<< orphan*/  C7 ; 
 int /*<<< orphan*/  D2 ; 
 int /*<<< orphan*/  D6 ; 
 int /*<<< orphan*/  D7 ; 
 int /*<<< orphan*/  E6 ; 
 int /*<<< orphan*/  F0 ; 
 int /*<<< orphan*/  F1 ; 
 int /*<<< orphan*/  F4 ; 
 int /*<<< orphan*/  F5 ; 
 int /*<<< orphan*/  F6 ; 
 int /*<<< orphan*/  F7 ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/  capSetup () ; 
 int /*<<< orphan*/  i2c_init () ; 
 int /*<<< orphan*/  matrix ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setPinInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeDataToTS (int,int) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 

void matrix_init(void) {

  i2c_init();

  //Motor enable
  setPinOutput(E6);
  //Motor PWM
  setPinOutput(D7);

  //Power LED
  setPinOutput(B7);
  writePinHigh(B7);

  //LEDs Columns
  setPinOutput(F7);
  setPinOutput(F6);
  setPinOutput(F5);
  setPinOutput(F4);
  setPinOutput(F1);
  setPinOutput(F0);

  //LEDs Rows
  setPinOutput(D6);
  setPinOutput(B4);
  setPinOutput(B5);
  setPinOutput(B6);
  setPinOutput(C6);
  setPinOutput(C7);

  //Capacitive Interrupt
  setPinInput(D2);

  capSetup();
  writeDataToTS(0x06, 0x12); //Calibrate capacitive touch IC

  memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));

  matrix_init_quantum();
}