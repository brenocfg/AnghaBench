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
struct xfs_pwork_ctl {int /*<<< orphan*/  nr_work; int /*<<< orphan*/  poll_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
xfs_pwork_poll(
	struct xfs_pwork_ctl	*pctl)
{
	while (wait_event_timeout(pctl->poll_wait,
				atomic_read(&pctl->nr_work) == 0, HZ) == 0)
		touch_softlockup_watchdog();
}