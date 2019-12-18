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
struct TYPE_2__ {scalar_t__ level; int enable; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (scalar_t__) ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  eeconfig_update_backlight (int /*<<< orphan*/ ) ; 

void backlight_decrease(void) {
    if (backlight_config.level > 0) {
        backlight_config.level--;
        backlight_config.enable = !!backlight_config.level;
        eeconfig_update_backlight(backlight_config.raw);
    }
    dprintf("backlight decrease: %u\n", backlight_config.level);
    backlight_set(backlight_config.level);
}