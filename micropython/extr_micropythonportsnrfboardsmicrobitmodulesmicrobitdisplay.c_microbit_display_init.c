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

/* Variables and functions */
 int MAX_ROW_PIN ; 
 int MIN_COLUMN_PIN ; 
 int /*<<< orphan*/  nrf_gpio_cfg_output (int) ; 

void microbit_display_init(void) {
    //  Set pins as output.
    for (int i = MIN_COLUMN_PIN; i <= MAX_ROW_PIN; i++) {
        nrf_gpio_cfg_output(i);
    }
}