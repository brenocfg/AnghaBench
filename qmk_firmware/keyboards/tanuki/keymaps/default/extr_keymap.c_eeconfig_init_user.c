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
struct TYPE_2__ {int layer_rgb; scalar_t__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_update_user (scalar_t__) ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ user_config ; 

void eeconfig_init_user(void) { // in case EEPROM is reset, set up our custom config
    user_config.raw = 0;
    user_config.layer_rgb = true; // enable per-layer RGB by default
    eeconfig_update_user(user_config.raw);
    rgblight_enable();
    rgblight_sethsv(0,10,255);
    rgblight_mode(1);
}