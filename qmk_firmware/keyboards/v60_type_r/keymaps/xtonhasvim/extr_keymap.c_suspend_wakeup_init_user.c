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
struct TYPE_4__ {int /*<<< orphan*/  level; int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 TYPE_2__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_read_backlight () ; 
 int /*<<< orphan*/  eeconfig_read_rgblight () ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 

void suspend_wakeup_init_user(void)
{
  rgblight_config.raw = eeconfig_read_rgblight();
  backlight_config.raw = eeconfig_read_backlight();

  backlight_set(backlight_config.level);
  rgblight_set();
}