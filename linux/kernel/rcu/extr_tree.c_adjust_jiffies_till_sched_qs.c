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
 int HZ ; 
 int RCU_JIFFIES_FQS_DIV ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  jiffies_till_first_fqs ; 
 int /*<<< orphan*/  jiffies_till_next_fqs ; 
 scalar_t__ jiffies_till_sched_qs ; 
 int /*<<< orphan*/  jiffies_to_sched_qs ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 

__attribute__((used)) static void adjust_jiffies_till_sched_qs(void)
{
	unsigned long j;

	/* If jiffies_till_sched_qs was specified, respect the request. */
	if (jiffies_till_sched_qs != ULONG_MAX) {
		WRITE_ONCE(jiffies_to_sched_qs, jiffies_till_sched_qs);
		return;
	}
	/* Otherwise, set to third fqs scan, but bound below on large system. */
	j = READ_ONCE(jiffies_till_first_fqs) +
		      2 * READ_ONCE(jiffies_till_next_fqs);
	if (j < HZ / 10 + nr_cpu_ids / RCU_JIFFIES_FQS_DIV)
		j = HZ / 10 + nr_cpu_ids / RCU_JIFFIES_FQS_DIV;
	pr_info("RCU calculated value of scheduler-enlistment delay is %ld jiffies.\n", j);
	WRITE_ONCE(jiffies_to_sched_qs, j);
}