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
struct TYPE_2__ {int rgb_layer_change; scalar_t__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRASHNA_UNICODE_MODE ; 
 int /*<<< orphan*/  EECONFIG_UNICODEMODE ; 
 int /*<<< orphan*/  eeconfig_init_keymap () ; 
 int /*<<< orphan*/  eeconfig_update_user (scalar_t__) ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unicode_input_mode () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 
 TYPE_1__ userspace_config ; 

void eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_layer_change = true;
    eeconfig_update_user(userspace_config.raw);
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(DRASHNA_UNICODE_MODE);
    get_unicode_input_mode();
#else
    eeprom_update_byte(EECONFIG_UNICODEMODE, DRASHNA_UNICODE_MODE);
#endif
    eeconfig_init_keymap();
    keyboard_init();
}