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
struct TYPE_2__ {int level; int enable; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  _delay_us (int) ; 
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 int /*<<< orphan*/  eeconfig_update_backlight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int,int,int) ; 

void matrix_init_user(void) {
    // Set LED's to max
    _delay_us(300);
    backlight_config.level = 2;
    backlight_config.enable = 1;
    eeconfig_update_backlight(backlight_config.raw);
    backlight_set(backlight_config.level);
    // Set RGB to rainbow mood light
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(120,255,255);
    rgblight_mode(6);
}