#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 TYPE_1__ gdth_timer ; 
 int gdth_timer_running ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void gdth_timer_init(void)
{
	if (gdth_timer_running)
		return;
	gdth_timer_running = 1;
	TRACE2(("gdth_detect(): Initializing timer !\n"));
	gdth_timer.expires = jiffies + HZ;
	add_timer(&gdth_timer);
}