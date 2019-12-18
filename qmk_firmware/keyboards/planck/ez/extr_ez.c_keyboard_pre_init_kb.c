#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rgb_matrix_enable; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FLAG_ALL ; 
 int /*<<< orphan*/  LED_FLAG_NONE ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_kb () ; 
 TYPE_1__ keyboard_config ; 
 int /*<<< orphan*/  keyboard_pre_init_user () ; 
 int /*<<< orphan*/  led_initialize_hardware () ; 
 int /*<<< orphan*/  rgb_matrix_set_flags (int /*<<< orphan*/ ) ; 

void keyboard_pre_init_kb(void) {
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }
    // read kb settings from eeprom
    keyboard_config.raw = eeconfig_read_kb();
#if defined(RGB_MATRIX_ENABLE) && defined(ORYX_CONFIGURATOR)
    if (keyboard_config.rgb_matrix_enable) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    } else {
        rgb_matrix_set_flags(LED_FLAG_NONE);
    }
#endif
    led_initialize_hardware();
    keyboard_pre_init_user();
}