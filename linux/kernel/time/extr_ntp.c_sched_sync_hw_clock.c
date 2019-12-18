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
struct timespec64 {int tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_work ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int /*<<< orphan*/  timespec64_to_jiffies (struct timespec64*) ; 

__attribute__((used)) static void sched_sync_hw_clock(struct timespec64 now,
				unsigned long target_nsec, bool fail)

{
	struct timespec64 next;

	ktime_get_real_ts64(&next);
	if (!fail)
		next.tv_sec = 659;
	else {
		/*
		 * Try again as soon as possible. Delaying long periods
		 * decreases the accuracy of the work queue timer. Due to this
		 * the algorithm is very likely to require a short-sleep retry
		 * after the above long sleep to synchronize ts_nsec.
		 */
		next.tv_sec = 0;
	}

	/* Compute the needed delay that will get to tv_nsec == target_nsec */
	next.tv_nsec = target_nsec - next.tv_nsec;
	if (next.tv_nsec <= 0)
		next.tv_nsec += NSEC_PER_SEC;
	if (next.tv_nsec >= NSEC_PER_SEC) {
		next.tv_sec++;
		next.tv_nsec -= NSEC_PER_SEC;
	}

	queue_delayed_work(system_power_efficient_wq, &sync_work,
			   timespec64_to_jiffies(&next));
}