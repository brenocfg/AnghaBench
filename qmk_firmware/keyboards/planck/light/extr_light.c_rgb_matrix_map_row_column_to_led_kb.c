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

uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
    // Spacebar has 2 leds 41 & 42, so add 42 to the array here, and 41 will be added
    // by the default lookup code that runs after this
    if (row == 3 && column == 5) {
        led_i[0] = 42;
        return 1;
    }
    return 0;
}