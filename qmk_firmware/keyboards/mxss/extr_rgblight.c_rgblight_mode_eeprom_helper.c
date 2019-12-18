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
typedef  int uint8_t ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; int /*<<< orphan*/  raw; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int RGBLIGHT_MODES ; 
 int /*<<< orphan*/  eeconfig_update_rgblight (int /*<<< orphan*/ ) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_timer_disable () ; 
 int /*<<< orphan*/  rgblight_timer_enable () ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void rgblight_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
  if (!rgblight_config.enable) {
    return;
  }
  if (mode < 1) {
    rgblight_config.mode = 1;
  } else if (mode > RGBLIGHT_MODES) {
    rgblight_config.mode = RGBLIGHT_MODES;
  } else {
    rgblight_config.mode = mode;
  }
  if (write_to_eeprom) {
    eeconfig_update_rgblight(rgblight_config.raw);
    xprintf("rgblight mode [EEPROM]: %u\n", rgblight_config.mode);
  } else {
    xprintf("rgblight mode [NOEEPROM]: %u\n", rgblight_config.mode);
  }
  if (rgblight_config.mode == 1) {
    #ifdef RGBLIGHT_ANIMATIONS
      rgblight_timer_disable();
    #endif
  } else if ((rgblight_config.mode >= 2 && rgblight_config.mode <= 24) ||
	     rgblight_config.mode == 35 ) {
    // MODE 2-5, breathing
    // MODE 6-8, rainbow mood
    // MODE 9-14, rainbow swirl
    // MODE 15-20, snake
    // MODE 21-23, knight
    // MODE 24, xmas
    // MODE 35  RGB test

    #ifdef RGBLIGHT_ANIMATIONS
      rgblight_timer_enable();
    #endif
  } else if (rgblight_config.mode >= 25 && rgblight_config.mode <= 34) {
    // MODE 25-34, static gradient

    #ifdef RGBLIGHT_ANIMATIONS
      rgblight_timer_disable();
    #endif
  }
  rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
}