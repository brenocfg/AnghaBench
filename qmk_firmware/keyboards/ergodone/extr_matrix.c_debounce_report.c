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
typedef  int matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBOUNCE ; 
 int MATRIX_COLS ; 
 int /*<<< orphan*/ * debounce_matrix ; 

void debounce_report(matrix_row_t change, uint8_t row) {
  for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
    if (change & (1 << i)) {
      debounce_matrix[row * MATRIX_COLS + i] = DEBOUNCE;
    }
  }
}