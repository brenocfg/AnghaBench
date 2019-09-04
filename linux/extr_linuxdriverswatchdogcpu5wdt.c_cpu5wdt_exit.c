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
struct TYPE_2__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  stop; scalar_t__ queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU5WDT_EXTENT ; 
 TYPE_1__ cpu5wdt_device ; 
 int /*<<< orphan*/  cpu5wdt_misc ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpu5wdt_exit(void)
{
	if (cpu5wdt_device.queue) {
		cpu5wdt_device.queue = 0;
		wait_for_completion(&cpu5wdt_device.stop);
		del_timer(&cpu5wdt_device.timer);
	}

	misc_deregister(&cpu5wdt_misc);

	release_region(port, CPU5WDT_EXTENT);

}