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
struct TYPE_2__ {int rgb_matrix_enable; int led_level; scalar_t__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_init_user () ; 
 int /*<<< orphan*/  eeconfig_update_kb (scalar_t__) ; 
 TYPE_1__ keyboard_config ; 

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    keyboard_config.raw = 0;
    keyboard_config.rgb_matrix_enable = true;
    keyboard_config.led_level = 4;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}