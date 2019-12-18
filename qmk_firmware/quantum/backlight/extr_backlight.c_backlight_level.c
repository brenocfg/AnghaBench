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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int enable; scalar_t__ level; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 scalar_t__ BACKLIGHT_LEVELS ; 
 TYPE_1__ backlight_config ; 
 int /*<<< orphan*/  backlight_set (scalar_t__) ; 
 int /*<<< orphan*/  eeconfig_update_backlight (int /*<<< orphan*/ ) ; 

void backlight_level(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) level = BACKLIGHT_LEVELS;
    backlight_config.level  = level;
    backlight_config.enable = !!backlight_config.level;
    eeconfig_update_backlight(backlight_config.raw);
    backlight_set(backlight_config.level);
}