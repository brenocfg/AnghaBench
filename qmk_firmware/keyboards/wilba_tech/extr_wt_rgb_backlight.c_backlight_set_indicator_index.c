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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ MATRIX_ROWS ; 
 int /*<<< orphan*/  map_row_column_to_led (scalar_t__,scalar_t__,scalar_t__*) ; 

void backlight_set_indicator_index( uint8_t *index, uint8_t row, uint8_t column )
{
    if ( row >= MATRIX_ROWS )
    {
        // Special value, 255=none, 254=all
        *index = row;
    }
    else
    {
        map_row_column_to_led( row, column, index );
    }
}