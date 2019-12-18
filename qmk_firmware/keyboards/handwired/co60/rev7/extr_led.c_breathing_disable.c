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
struct TYPE_2__ {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  breathing_interrupt_disable () ; 
 TYPE_1__ kb_backlight_config ; 

void breathing_disable(void)
{
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(kb_backlight_config.level);
}