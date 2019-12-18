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
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ GetCurrentTimestamp () ; 
 scalar_t__ GetStandbyLimitTime () ; 
 int /*<<< orphan*/  pg_usleep (int) ; 
 int standbyWait_us ; 

__attribute__((used)) static bool
WaitExceedsMaxStandbyDelay(void)
{
	TimestampTz ltime;

	CHECK_FOR_INTERRUPTS();

	/* Are we past the limit time? */
	ltime = GetStandbyLimitTime();
	if (ltime && GetCurrentTimestamp() >= ltime)
		return true;

	/*
	 * Sleep a bit (this is essential to avoid busy-waiting).
	 */
	pg_usleep(standbyWait_us);

	/*
	 * Progressively increase the sleep times, but not to more than 1s, since
	 * pg_usleep isn't interruptible on some platforms.
	 */
	standbyWait_us *= 2;
	if (standbyWait_us > 1000000)
		standbyWait_us = 1000000;

	return false;
}