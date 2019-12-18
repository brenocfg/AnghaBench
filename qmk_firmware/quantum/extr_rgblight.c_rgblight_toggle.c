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
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,int) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_disable () ; 
 int /*<<< orphan*/  rgblight_enable () ; 

void rgblight_toggle(void) {
    dprintf("rgblight toggle [EEPROM]: rgblight_config.enable = %u\n", !rgblight_config.enable);
    if (rgblight_config.enable) {
        rgblight_disable();
    } else {
        rgblight_enable();
    }
}