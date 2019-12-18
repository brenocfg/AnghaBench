#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* raw; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 int LED_DRIVER_LED_COUNT ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_debug_led_matrix () ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 void* eeconfig_read_led_matrix () ; 
 int /*<<< orphan*/  eeconfig_update_led_matrix_default () ; 
 int* g_key_hit ; 
 TYPE_2__ led_matrix_config ; 
 TYPE_1__ led_matrix_driver ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void led_matrix_init(void) {
    led_matrix_driver.init();

    // Wait half a second for the driver to finish initializing
    wait_ms(500);

    // clear the key hits
    for (int led = 0; led < LED_DRIVER_LED_COUNT; led++) {
        g_key_hit[led] = 255;
    }

    if (!eeconfig_is_enabled()) {
        dprintf("led_matrix_init_drivers eeconfig is not enabled.\n");
        eeconfig_init();
        eeconfig_update_led_matrix_default();
    }

    led_matrix_config.raw = eeconfig_read_led_matrix();

    if (!led_matrix_config.mode) {
        dprintf("led_matrix_init_drivers led_matrix_config.mode = 0. Write default values to EEPROM.\n");
        eeconfig_update_led_matrix_default();
        led_matrix_config.raw = eeconfig_read_led_matrix();
    }

    eeconfig_debug_led_matrix();  // display current eeprom values
}