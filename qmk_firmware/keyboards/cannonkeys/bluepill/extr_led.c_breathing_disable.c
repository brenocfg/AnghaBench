#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  breathing_interrupt_disable () ; 
 int /*<<< orphan*/  get_backlight_level () ; 
 int /*<<< orphan*/  printf (char*) ; 

void breathing_disable(void)
{
    printf("breathing_disable()\n");
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(get_backlight_level());
}