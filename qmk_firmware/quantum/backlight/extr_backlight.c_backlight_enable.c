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
struct TYPE_2__ {int enable; int raw; int level; } ;

/* Variables and functions */
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_update_backlight (int) ; 

void backlight_enable(void) {
    if (backlight_config.enable) return;  // do nothing if backlight is already on

    backlight_config.enable = true;
    if (backlight_config.raw == 1)  // enabled but level == 0
        backlight_config.level = 1;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight enable\n");
    backlight_set(backlight_config.level);
}