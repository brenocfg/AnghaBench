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
struct TYPE_2__ {int enable; int mode; int sat; int /*<<< orphan*/  raw; scalar_t__ speed; int /*<<< orphan*/  val; scalar_t__ hue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_LIMIT_VAL ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_update_rgblight (int /*<<< orphan*/ ) ; 
 TYPE_1__ rgblight_config ; 

void eeconfig_update_rgblight_default(void) {
  dprintf("eeconfig_update_rgblight_default\n");
  rgblight_config.enable = 1;
  rgblight_config.mode = 1;
  rgblight_config.hue = 0;
  rgblight_config.sat = 255;
  rgblight_config.val = RGBLIGHT_LIMIT_VAL;
  rgblight_config.speed = 0;
  eeconfig_update_rgblight(rgblight_config.raw);
}