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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t MATRIX_COLS ; 
 size_t MATRIX_ROWS ; 
 int /*<<< orphan*/ ** g_map_row_column_to_led ; 
 size_t pgm_read_byte (int /*<<< orphan*/ *) ; 

void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led )
{
    *led = 255;
    if ( row < MATRIX_ROWS && column < MATRIX_COLS )
    {
        *led = pgm_read_byte(&g_map_row_column_to_led[row][column]);
    }
}