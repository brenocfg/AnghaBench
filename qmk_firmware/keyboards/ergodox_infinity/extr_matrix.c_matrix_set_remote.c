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
typedef  int /*<<< orphan*/  matrix_row_t ;

/* Variables and functions */
 int LOCAL_MATRIX_ROWS ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/ * matrix ; 

void matrix_set_remote(matrix_row_t* rows, uint8_t index) {
    uint8_t offset = 0;
#ifdef MASTER_IS_ON_RIGHT
    offset = MATRIX_ROWS - LOCAL_MATRIX_ROWS * (index + 2);
#else
    offset = LOCAL_MATRIX_ROWS * (index + 1);
#endif
    for (int row = 0; row < LOCAL_MATRIX_ROWS; row++) {
        matrix[offset + row] = rows[row];
    }
}