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
typedef  int /*<<< orphan*/  timer_t ;

/* Variables and functions */
 int TIMER_SECS ; 
 int alarmcount ; 
 int check_timer_latency (int,int const) ; 
 int setup_timer (int,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  timer_delete (int /*<<< orphan*/ ) ; 

int do_timer(int clock_id, int flags)
{
	timer_t tm1;
	const int interval = TIMER_SECS;
	int err;

	err = setup_timer(clock_id, flags, interval, &tm1);
	/* Unsupported case - return 0 to not fail the test */
	if (err)
		return err == 1 ? 0 : err;

	while (alarmcount < 5)
		sleep(1);

	timer_delete(tm1);
	return check_timer_latency(flags, interval);
}