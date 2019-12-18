#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t row; size_t col; } ;
struct TYPE_5__ {TYPE_1__ matrix_co; } ;
typedef  TYPE_2__ led_matrix ;

/* Variables and functions */
 size_t LED_DRIVER_LED_COUNT ; 
 TYPE_2__* g_leds ; 

void map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i, uint8_t *led_count) {
    led_matrix led;
    *led_count = 0;

    for (uint8_t i = 0; i < LED_DRIVER_LED_COUNT; i++) {
        // map_index_to_led(i, &led);
        led = g_leds[i];
        if (row == led.matrix_co.row && column == led.matrix_co.col) {
            led_i[*led_count] = i;
            (*led_count)++;
        }
    }
}