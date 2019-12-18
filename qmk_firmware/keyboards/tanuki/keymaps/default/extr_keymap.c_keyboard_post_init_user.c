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
struct TYPE_2__ {scalar_t__ layer_rgb; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_read_user () ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ user_config ; 

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    if(user_config.layer_rgb) {
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(1);
        rgblight_sethsv_noeeprom(0,10,255);
    }
}