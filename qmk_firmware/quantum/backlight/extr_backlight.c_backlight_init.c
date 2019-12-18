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
struct TYPE_2__ {scalar_t__ level; scalar_t__ enable; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 scalar_t__ BACKLIGHT_LEVELS ; 
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (scalar_t__) ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_backlight () ; 

void backlight_init(void) {
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    backlight_config.raw = eeconfig_read_backlight();
    if (backlight_config.level > BACKLIGHT_LEVELS) {
        backlight_config.level = BACKLIGHT_LEVELS;
    }
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
}