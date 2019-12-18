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
typedef  int /*<<< orphan*/  timeout ;
struct timeval {int tv_sec; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int check_alarmcount (int,int const) ; 
 int check_timer_latency (int,int const) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int setup_timer (int,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_delete (int /*<<< orphan*/ ) ; 

int do_timer_oneshot(int clock_id, int flags)
{
	timer_t tm1;
	const int interval = 0;
	struct timeval timeout;
	int err;

	err = setup_timer(clock_id, flags, interval, &tm1);
	/* Unsupported case - return 0 to not fail the test */
	if (err)
		return err == 1 ? 0 : err;

	memset(&timeout, 0, sizeof(timeout));
	timeout.tv_sec = 5;
	do {
		err = select(0, NULL, NULL, NULL, &timeout);
	} while (err == -1 && errno == EINTR);

	timer_delete(tm1);
	err = check_timer_latency(flags, interval);
	err |= check_alarmcount(flags, interval);
	return err;
}