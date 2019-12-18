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
typedef  int matrix_row_t ;

/* Variables and functions */
 int PINB ; 
 int PINF ; 
 int ROW_SHIFTER ; 

__attribute__((used)) inline static matrix_row_t optimized_col_reader(void) {
    //MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }
    return (PINB & (1 << 6) ? 0 : (ROW_SHIFTER << 0)) |
          (PINB & (1 << 2) ? 0 : (ROW_SHIFTER << 1)) |
          (PINB & (1 << 3) ? 0 : (ROW_SHIFTER << 2)) |
          (PINB & (1 << 1) ? 0 : (ROW_SHIFTER << 3)) |
          (PINF & (1 << 7) ? 0 : (ROW_SHIFTER << 4)) |
          (PINF & (1 << 6) ? 0 : (ROW_SHIFTER << 5)) |
          (PINF & (1 << 5) ? 0 : (ROW_SHIFTER << 6)) |
          (PINF & (1 << 4) ? 0 : (ROW_SHIFTER << 7));
}