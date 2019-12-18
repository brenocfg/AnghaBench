#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ strobe_row; int* pins_for_brightness; } ;
typedef  TYPE_1__ microbit_display_obj_t ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_6__ {int** image_buffer; } ;

/* Variables and functions */
 int COLUMN_COUNT ; 
 int /*<<< orphan*/  COLUMN_PINS_MASK ; 
 int MAX_BRIGHTNESS ; 
 int MIN_COLUMN_PIN ; 
 scalar_t__ MIN_ROW_PIN ; 
 int /*<<< orphan*/  NRF_GPIO ; 
 scalar_t__ ROW_COUNT ; 
 TYPE_3__** display_map ; 
 TYPE_2__ microbit_display_obj ; 
 int /*<<< orphan*/  nrf_gpio_pin_clear (scalar_t__) ; 
 int /*<<< orphan*/  nrf_gpio_pin_set (scalar_t__) ; 
 int /*<<< orphan*/  nrf_gpio_port_out_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nrf_gpio_port_out_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void displayAdvanceRow(microbit_display_obj_t * p_display) {
    /* Clear all of the column bits */
    nrf_gpio_port_out_set(NRF_GPIO, COLUMN_PINS_MASK);
    /* Clear the strobe bit for this row */
    nrf_gpio_pin_clear(p_display->strobe_row + MIN_ROW_PIN);

    /* Move to the next row.  Before this, "this row" refers to the row
     * manipulated by the previous invocation of this function.  After this,
     * "this row" refers to the row manipulated by the current invocation of
     * this function. */
    p_display->strobe_row++;

    // Reset the row counts and bit mask when we have hit the max.
    if (p_display->strobe_row == ROW_COUNT) {
        p_display->strobe_row = 0;
    }

    // Set pin for this row.
    // Prepare row for rendering.
    for (int i = 0; i <= MAX_BRIGHTNESS; i++) {
        p_display->pins_for_brightness[i] = 0;
    }
    for (int i = 0; i < COLUMN_COUNT; i++) {
        int x = display_map[i][p_display->strobe_row].x;
        int y = display_map[i][p_display->strobe_row].y;
        int brightness = microbit_display_obj.image_buffer[x][y];
        p_display->pins_for_brightness[brightness] |= (1<<(i+MIN_COLUMN_PIN));
        (void)brightness;
    }
    /* Enable the strobe bit for this row */
    nrf_gpio_pin_set(p_display->strobe_row + MIN_ROW_PIN);
    /* Enable the column bits for all pins that need to be on. */
    nrf_gpio_port_out_clear(NRF_GPIO, p_display->pins_for_brightness[MAX_BRIGHTNESS]);
}