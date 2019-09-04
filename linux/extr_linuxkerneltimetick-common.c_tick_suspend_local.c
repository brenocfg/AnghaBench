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
struct tick_device {int /*<<< orphan*/  evtdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clockevents_shutdown (int /*<<< orphan*/ ) ; 
 struct tick_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_cpu_device ; 

void tick_suspend_local(void)
{
	struct tick_device *td = this_cpu_ptr(&tick_cpu_device);

	clockevents_shutdown(td->evtdev);
}