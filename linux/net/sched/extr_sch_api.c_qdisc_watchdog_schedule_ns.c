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
typedef  scalar_t__ u64 ;
struct qdisc_watchdog {scalar_t__ last_expires; int /*<<< orphan*/  timer; int /*<<< orphan*/  qdisc; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_PINNED ; 
 int /*<<< orphan*/  __QDISC_STATE_DEACTIVATED ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (scalar_t__) ; 
 TYPE_1__* qdisc_root_sleeping (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qdisc_watchdog_schedule_ns(struct qdisc_watchdog *wd, u64 expires)
{
	if (test_bit(__QDISC_STATE_DEACTIVATED,
		     &qdisc_root_sleeping(wd->qdisc)->state))
		return;

	if (wd->last_expires == expires)
		return;

	wd->last_expires = expires;
	hrtimer_start(&wd->timer,
		      ns_to_ktime(expires),
		      HRTIMER_MODE_ABS_PINNED);
}