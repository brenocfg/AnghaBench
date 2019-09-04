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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 int UNSUPPORTED ; 
 scalar_t__ clock_gettime (int,struct timespec*) ; 
 scalar_t__ clock_nanosleep (int,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_order (struct timespec,struct timespec) ; 
 struct timespec timespec_add (struct timespec,long long) ; 

int nanosleep_test(int clockid, long long ns)
{
	struct timespec now, target, rel;

	/* First check abs time */
	if (clock_gettime(clockid, &now))
		return UNSUPPORTED;
	target = timespec_add(now, ns);

	if (clock_nanosleep(clockid, TIMER_ABSTIME, &target, NULL))
		return UNSUPPORTED;
	clock_gettime(clockid, &now);

	if (!in_order(target, now))
		return -1;

	/* Second check reltime */
	clock_gettime(clockid, &now);
	rel.tv_sec = 0;
	rel.tv_nsec = 0;
	rel = timespec_add(rel, ns);
	target = timespec_add(now, ns);
	clock_nanosleep(clockid, 0, &rel, NULL);
	clock_gettime(clockid, &now);

	if (!in_order(target, now))
		return -1;
	return 0;
}