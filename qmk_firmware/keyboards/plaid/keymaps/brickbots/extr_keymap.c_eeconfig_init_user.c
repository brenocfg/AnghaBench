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
struct TYPE_2__ {scalar_t__ raw; int /*<<< orphan*/  green_mode; int /*<<< orphan*/  red_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEDMODE_MODS ; 
 int /*<<< orphan*/  LEDMODE_ON ; 
 int /*<<< orphan*/  eeconfig_update_user (scalar_t__) ; 
 TYPE_1__ led_config ; 

void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_ON;
  led_config.green_mode = LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}