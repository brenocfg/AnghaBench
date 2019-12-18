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
typedef  int TimeOffset ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int GetCurrentTimestamp () ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_BASE_BACKUP_THROTTLE ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int WaitLatch (int /*<<< orphan*/ ,int,long,int /*<<< orphan*/ ) ; 
 size_t elapsed_min_unit ; 
 int throttled_last ; 
 size_t throttling_counter ; 
 size_t throttling_sample ; 

__attribute__((used)) static void
throttle(size_t increment)
{
	TimeOffset	elapsed_min;

	if (throttling_counter < 0)
		return;

	throttling_counter += increment;
	if (throttling_counter < throttling_sample)
		return;

	/* How much time should have elapsed at minimum? */
	elapsed_min = elapsed_min_unit *
		(throttling_counter / throttling_sample);

	/*
	 * Since the latch could be set repeatedly because of concurrently WAL
	 * activity, sleep in a loop to ensure enough time has passed.
	 */
	for (;;)
	{
		TimeOffset	elapsed,
					sleep;
		int			wait_result;

		/* Time elapsed since the last measurement (and possible wake up). */
		elapsed = GetCurrentTimestamp() - throttled_last;

		/* sleep if the transfer is faster than it should be */
		sleep = elapsed_min - elapsed;
		if (sleep <= 0)
			break;

		ResetLatch(MyLatch);

		/* We're eating a potentially set latch, so check for interrupts */
		CHECK_FOR_INTERRUPTS();

		/*
		 * (TAR_SEND_SIZE / throttling_sample * elapsed_min_unit) should be
		 * the maximum time to sleep. Thus the cast to long is safe.
		 */
		wait_result = WaitLatch(MyLatch,
								WL_LATCH_SET | WL_TIMEOUT | WL_EXIT_ON_PM_DEATH,
								(long) (sleep / 1000),
								WAIT_EVENT_BASE_BACKUP_THROTTLE);

		if (wait_result & WL_LATCH_SET)
			CHECK_FOR_INTERRUPTS();

		/* Done waiting? */
		if (wait_result & WL_TIMEOUT)
			break;
	}

	/*
	 * As we work with integers, only whole multiple of throttling_sample was
	 * processed. The rest will be done during the next call of this function.
	 */
	throttling_counter %= throttling_sample;

	/*
	 * Time interval for the remaining amount and possible next increments
	 * starts now.
	 */
	throttled_last = GetCurrentTimestamp();
}