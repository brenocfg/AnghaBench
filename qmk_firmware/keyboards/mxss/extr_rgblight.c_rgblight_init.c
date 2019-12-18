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
struct TYPE_2__ {int /*<<< orphan*/  mode; scalar_t__ enable; void* raw; } ;

/* Variables and functions */
 int debug_enable ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_debug_rgblight () ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 void* eeconfig_read_rgblight () ; 
 int /*<<< orphan*/  eeconfig_update_rgblight_default () ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_timer_init () ; 

void rgblight_init(void) {
  debug_enable = 1; // Debug ON!
  dprintf("rgblight_init called.\n");
  dprintf("rgblight_init start!\n");
  if (!eeconfig_is_enabled()) {
    dprintf("rgblight_init eeconfig is not enabled.\n");
    eeconfig_init();
    eeconfig_update_rgblight_default();
  }
  rgblight_config.raw = eeconfig_read_rgblight();
  if (!rgblight_config.mode) {
    dprintf("rgblight_init rgblight_config.mode = 0. Write default values to EEPROM.\n");
    eeconfig_update_rgblight_default();
    rgblight_config.raw = eeconfig_read_rgblight();
  }
  eeconfig_debug_rgblight(); // display current eeprom values

  #ifdef RGBLIGHT_ANIMATIONS
    rgblight_timer_init(); // setup the timer
  #endif

  if (rgblight_config.enable) {
    rgblight_mode_noeeprom(rgblight_config.mode);
  }
}