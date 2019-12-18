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
struct taprio_sched {int dummy; } ;
struct sched_gate_list {int cycle_time; } ;
struct Qdisc {int dummy; } ;
typedef  int s64 ;
typedef  int ktime_t ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ WARN_ON (int) ; 
 int div64_s64 (int /*<<< orphan*/ ,int) ; 
 int ktime_add_ns (int,int) ; 
 scalar_t__ ktime_after (int,int) ; 
 int /*<<< orphan*/  ktime_sub_ns (int,int) ; 
 struct taprio_sched* qdisc_priv (struct Qdisc*) ; 
 int sched_base_time (struct sched_gate_list*) ; 
 int taprio_get_time (struct taprio_sched*) ; 

__attribute__((used)) static int taprio_get_start_time(struct Qdisc *sch,
				 struct sched_gate_list *sched,
				 ktime_t *start)
{
	struct taprio_sched *q = qdisc_priv(sch);
	ktime_t now, base, cycle;
	s64 n;

	base = sched_base_time(sched);
	now = taprio_get_time(q);

	if (ktime_after(base, now)) {
		*start = base;
		return 0;
	}

	cycle = sched->cycle_time;

	/* The qdisc is expected to have at least one sched_entry.  Moreover,
	 * any entry must have 'interval' > 0. Thus if the cycle time is zero,
	 * something went really wrong. In that case, we should warn about this
	 * inconsistent state and return error.
	 */
	if (WARN_ON(!cycle))
		return -EFAULT;

	/* Schedule the start time for the beginning of the next
	 * cycle.
	 */
	n = div64_s64(ktime_sub_ns(now, base), cycle);
	*start = ktime_add_ns(base, (n + 1) * cycle);
	return 0;
}