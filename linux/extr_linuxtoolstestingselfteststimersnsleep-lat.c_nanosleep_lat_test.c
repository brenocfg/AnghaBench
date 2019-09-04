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
struct timespec {long long tv_sec; long long tv_nsec; } ;

/* Variables and functions */
 long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 int UNRESONABLE_LATENCY ; 
 int UNSUPPORTED ; 
 scalar_t__ clock_gettime (int,struct timespec*) ; 
 scalar_t__ clock_nanosleep (int,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,long long) ; 
 struct timespec timespec_add (struct timespec,long long) ; 
 long long timespec_sub (struct timespec,struct timespec) ; 

int nanosleep_lat_test(int clockid, long long ns)
{
	struct timespec start, end, target;
	long long latency = 0;
	int i, count;

	target.tv_sec = ns/NSEC_PER_SEC;
	target.tv_nsec = ns%NSEC_PER_SEC;

	if (clock_gettime(clockid, &start))
		return UNSUPPORTED;
	if (clock_nanosleep(clockid, 0, &target, NULL))
		return UNSUPPORTED;

	count = 10;

	/* First check relative latency */
	clock_gettime(clockid, &start);
	for (i = 0; i < count; i++)
		clock_nanosleep(clockid, 0, &target, NULL);
	clock_gettime(clockid, &end);

	if (((timespec_sub(start, end)/count)-ns) > UNRESONABLE_LATENCY) {
		printf("Large rel latency: %lld ns :", (timespec_sub(start, end)/count)-ns);
		return -1;
	}

	/* Next check absolute latency */
	for (i = 0; i < count; i++) {
		clock_gettime(clockid, &start);
		target = timespec_add(start, ns);
		clock_nanosleep(clockid, TIMER_ABSTIME, &target, NULL);
		clock_gettime(clockid, &end);
		latency += timespec_sub(target, end);
	}

	if (latency/count > UNRESONABLE_LATENCY) {
		printf("Large abs latency: %lld ns :", latency/count);
		return -1;
	}

	return 0;
}