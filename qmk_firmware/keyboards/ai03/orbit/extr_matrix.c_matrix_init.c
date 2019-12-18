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

/* Variables and functions */
 int MATRIX_COLS ; 
 int* MATRIX_COL_PINS_RIGHT ; 
 int MATRIX_ROWS ; 
 int* MATRIX_ROW_PINS_RIGHT ; 
 scalar_t__ ROWS_PER_HAND ; 
 int* col_pins ; 
 int /*<<< orphan*/  debounce_init (scalar_t__) ; 
 int debug_enable ; 
 int debug_matrix ; 
 int debug_mouse ; 
 int /*<<< orphan*/  init_pins () ; 
 scalar_t__ isLeftHand ; 
 scalar_t__* matrix ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int* row_pins ; 
 scalar_t__ thatHand ; 
 scalar_t__ thisHand ; 

void matrix_init(void) {
  debug_enable = true;
  debug_matrix = true;
  debug_mouse  = true;

  // Set pinout for right half if pinout for that half is defined
  if (!isLeftHand) {
#ifdef MATRIX_ROW_PINS_RIGHT
    const uint8_t row_pins_right[MATRIX_ROWS] = MATRIX_ROW_PINS_RIGHT;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
      row_pins[i] = row_pins_right[i];
    }
#endif
#ifdef MATRIX_COL_PINS_RIGHT
    const uint8_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
      col_pins[i] = col_pins_right[i];
    }
#endif
  }

  thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
  thatHand = ROWS_PER_HAND - thisHand;

  // initialize key pins
  init_pins();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
  }

  debounce_init(ROWS_PER_HAND);

  matrix_init_quantum();
}