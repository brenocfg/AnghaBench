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
struct TYPE_2__ {int enable; int /*<<< orphan*/  raw; scalar_t__ speed; int /*<<< orphan*/  val; int /*<<< orphan*/  sat; scalar_t__ hue; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_LIMIT_VAL ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
 int /*<<< orphan*/  RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS ; 
 int /*<<< orphan*/  UINT8_MAX ; 
 int /*<<< orphan*/  eeconfig_update_rgblight (int /*<<< orphan*/ ) ; 
 TYPE_1__ rgblight_config ; 

void eeconfig_update_rgblight_default(void) {
    rgblight_config.enable = 1;
    rgblight_config.mode   = RGBLIGHT_MODE_STATIC_LIGHT;
    rgblight_config.hue    = 0;
    rgblight_config.sat    = UINT8_MAX;
    rgblight_config.val    = RGBLIGHT_LIMIT_VAL;
    rgblight_config.speed  = 0;
    RGBLIGHT_SPLIT_SET_CHANGE_MODEHSVS;
    eeconfig_update_rgblight(rgblight_config.raw);
}