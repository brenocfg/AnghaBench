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
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  all_timeouts_initialized ; 
 int /*<<< orphan*/  disable_alarm () ; 
 scalar_t__ num_active_timeouts ; 
 int /*<<< orphan*/  schedule_alarm (int /*<<< orphan*/ ) ; 

void
reschedule_timeouts(void)
{
	/* For flexibility, allow this to be called before we're initialized. */
	if (!all_timeouts_initialized)
		return;

	/* Disable timeout interrupts for safety. */
	disable_alarm();

	/* Reschedule the interrupt, if any timeouts remain active. */
	if (num_active_timeouts > 0)
		schedule_alarm(GetCurrentTimestamp());
}