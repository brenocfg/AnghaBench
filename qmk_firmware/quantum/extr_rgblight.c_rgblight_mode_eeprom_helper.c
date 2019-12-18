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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int restart; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; scalar_t__ mode; int /*<<< orphan*/  raw; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_MODES ; 
 scalar_t__ RGBLIGHT_MODE_STATIC_LIGHT ; 
 int /*<<< orphan*/  RGBLIGHT_SPLIT_SET_CHANGE_MODE ; 
 TYPE_2__ animation_status ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  eeconfig_update_rgblight (int /*<<< orphan*/ ) ; 
 scalar_t__ is_static_effect (scalar_t__) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_timer_disable () ; 
 int /*<<< orphan*/  rgblight_timer_enable () ; 

void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
    if (!rgblight_config.enable) {
        return;
    }
    if (mode < RGBLIGHT_MODE_STATIC_LIGHT) {
        rgblight_config.mode = RGBLIGHT_MODE_STATIC_LIGHT;
    } else if (mode > RGBLIGHT_MODES) {
        rgblight_config.mode = RGBLIGHT_MODES;
    } else {
        rgblight_config.mode = mode;
    }
    RGBLIGHT_SPLIT_SET_CHANGE_MODE;
    if (write_to_eeprom) {
        eeconfig_update_rgblight(rgblight_config.raw);
        dprintf("rgblight mode [EEPROM]: %u\n", rgblight_config.mode);
    } else {
        dprintf("rgblight mode [NOEEPROM]: %u\n", rgblight_config.mode);
    }
    if (is_static_effect(rgblight_config.mode)) {
#ifdef RGBLIGHT_USE_TIMER
        rgblight_timer_disable();
#endif
    } else {
#ifdef RGBLIGHT_USE_TIMER
        rgblight_timer_enable();
#endif
    }
#ifdef RGBLIGHT_USE_TIMER
    animation_status.restart = true;
#endif
    rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
}