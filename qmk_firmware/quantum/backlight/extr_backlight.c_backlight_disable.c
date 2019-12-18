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
struct TYPE_2__ {int enable; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  eeconfig_update_backlight (int /*<<< orphan*/ ) ; 

void backlight_disable(void) {
    if (!backlight_config.enable) return;  // do nothing if backlight is already off

    backlight_config.enable = false;
    eeconfig_update_backlight(backlight_config.raw);
    dprintf("backlight disable\n");
    backlight_set(0);
}