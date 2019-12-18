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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  B4 ; 
 int /*<<< orphan*/  B5 ; 
 int /*<<< orphan*/  B6 ; 
 int /*<<< orphan*/  C6 ; 
 int /*<<< orphan*/  C7 ; 
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
 scalar_t__ VIBRATE_LENGTH ; 
 int /*<<< orphan*/  _BV (int) ; 
 int /*<<< orphan*/  decodeArray (int,int*,int*) ; 
 scalar_t__ isTouchChangeDetected () ; 
 int /*<<< orphan*/ * matrix ; 
 int matrix_is_on (int,int) ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  touchClearCurrentDetections () ; 
 int touchDetectionRoutine () ; 
 scalar_t__ vibrate ; 
 int /*<<< orphan*/  writePin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

uint8_t matrix_scan(void) {
  if (isTouchChangeDetected()) {
    uint16_t dataIn = touchDetectionRoutine();
    if ((dataIn & 0b111100010001) > 0 && (dataIn & 0b000011101110) > 0) {
      uint8_t column = 10, row = 10;
      decodeArray(dataIn, &column, &row);
      if (column != 10 && row != 10) {
        vibrate = VIBRATE_LENGTH; //Trigger vibration
        matrix[row] = _BV(column);
      } else {
        memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
      }
    } else {
      memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    }
    touchClearCurrentDetections();
  }

  for (uint8_t c = 0; c < 6; c++) {
    for (uint8_t r = 0; r < 6; r++) {
      switch (r) {
        case 0: writePin(D6, matrix_is_on(r, c)); break;
        case 1: writePin(B4, matrix_is_on(r, c)); break;
        case 2: writePin(B5, matrix_is_on(r, c)); break;
        case 3: writePin(B6, matrix_is_on(r, c)); break;
        case 4: writePin(C6, matrix_is_on(r, c)); break;
        case 5: writePin(C7, matrix_is_on(r, c)); break;
      }

      switch (c) {
        case 0: writePin(F5, !matrix_is_on(r, c)); break;
        case 1: writePin(F4, !matrix_is_on(r, c)); break;
        case 2: writePin(F1, !matrix_is_on(r, c)); break;
        case 3: writePin(F0, !matrix_is_on(r, c)); break;
        case 4: writePin(F6, !matrix_is_on(r, c)); break;
        case 5: writePin(F7, !matrix_is_on(r, c)); break;
      }
    }
  }

  if (vibrate == VIBRATE_LENGTH) {
    writePinHigh(E6);
    writePinHigh(D7);
    vibrate--;
  }  else if (vibrate > 0) {
    vibrate--;
  } else if (vibrate == 0) {
    writePinLow(D7);
    writePinLow(E6);
  }

  matrix_scan_quantum();

  return 1;

}