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
struct tick_device {scalar_t__ mode; int /*<<< orphan*/  evtdev; } ;

/* Variables and functions */
 scalar_t__ TICKDEV_MODE_PERIODIC ; 
 int /*<<< orphan*/  clockevents_tick_resume (int /*<<< orphan*/ ) ; 
 struct tick_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_cpu_device ; 
 int tick_resume_check_broadcast () ; 
 int /*<<< orphan*/  tick_resume_oneshot () ; 
 int /*<<< orphan*/  tick_setup_periodic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tick_resume_local(void)
{
	struct tick_device *td = this_cpu_ptr(&tick_cpu_device);
	bool broadcast = tick_resume_check_broadcast();

	clockevents_tick_resume(td->evtdev);
	if (!broadcast) {
		if (td->mode == TICKDEV_MODE_PERIODIC)
			tick_setup_periodic(td->evtdev, 0);
		else
			tick_resume_oneshot();
	}
}