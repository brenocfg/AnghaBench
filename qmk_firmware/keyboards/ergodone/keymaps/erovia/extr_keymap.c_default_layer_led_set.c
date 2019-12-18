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
#define  COLEMAK 129 
#define  QWERTY 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 

void default_layer_led_set(void) {
    switch (biton32(eeconfig_read_default_layer())) {
      case COLEMAK:
        // LED2 for COLEMAK
        ergodox_right_led_2_on();
        break;
      case QWERTY:
        // LED3 for QWERTY
        ergodox_right_led_3_on();
        break;
    };
}