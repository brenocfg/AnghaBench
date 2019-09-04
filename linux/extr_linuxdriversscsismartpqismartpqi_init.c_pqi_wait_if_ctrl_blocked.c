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
struct pqi_ctrl_info {int /*<<< orphan*/  num_blocked_threads; int /*<<< orphan*/  block_requests_wait; } ;

/* Variables and functions */
 unsigned long NO_TIMEOUT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned long jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  pqi_ctrl_blocked (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 unsigned long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pqi_wait_if_ctrl_blocked(struct pqi_ctrl_info *ctrl_info,
	unsigned long timeout_msecs)
{
	unsigned long remaining_msecs;

	if (!pqi_ctrl_blocked(ctrl_info))
		return timeout_msecs;

	atomic_inc(&ctrl_info->num_blocked_threads);

	if (timeout_msecs == NO_TIMEOUT) {
		wait_event(ctrl_info->block_requests_wait,
			!pqi_ctrl_blocked(ctrl_info));
		remaining_msecs = timeout_msecs;
	} else {
		unsigned long remaining_jiffies;

		remaining_jiffies =
			wait_event_timeout(ctrl_info->block_requests_wait,
				!pqi_ctrl_blocked(ctrl_info),
				msecs_to_jiffies(timeout_msecs));
		remaining_msecs = jiffies_to_msecs(remaining_jiffies);
	}

	atomic_dec(&ctrl_info->num_blocked_threads);

	return remaining_msecs;
}