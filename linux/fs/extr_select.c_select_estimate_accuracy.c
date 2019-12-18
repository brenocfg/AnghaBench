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
typedef  scalar_t__ u64 ;
struct timespec64 {int dummy; } ;
struct TYPE_3__ {scalar_t__ timer_slack_ns; } ;

/* Variables and functions */
 scalar_t__ __estimate_accuracy (struct timespec64*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 scalar_t__ rt_task (TYPE_1__*) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 

u64 select_estimate_accuracy(struct timespec64 *tv)
{
	u64 ret;
	struct timespec64 now;

	/*
	 * Realtime tasks get a slack of 0 for obvious reasons.
	 */

	if (rt_task(current))
		return 0;

	ktime_get_ts64(&now);
	now = timespec64_sub(*tv, now);
	ret = __estimate_accuracy(&now);
	if (ret < current->timer_slack_ns)
		return current->timer_slack_ns;
	return ret;
}