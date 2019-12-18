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
struct TYPE_4__ {int level; int enable; } ;
struct TYPE_3__ {int enable; } ;

/* Variables and functions */
 TYPE_2__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 

void suspend_power_down_user(void)
{
  // rgb
  rgblight_config.enable = false;
  rgblight_set();

  // backlight
  /** I don't know why, but 3 means "off" and down is up */
  backlight_config.level = 3;
  backlight_config.enable = false;
  backlight_set(3);
}