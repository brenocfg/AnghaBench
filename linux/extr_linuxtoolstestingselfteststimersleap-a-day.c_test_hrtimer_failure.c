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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  clock_nanosleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 
 int error_found ; 
 int /*<<< orphan*/  in_order (struct timespec,struct timespec) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct timespec timespec_add (struct timespec,int) ; 

void test_hrtimer_failure(void)
{
	struct timespec now, target;

	clock_gettime(CLOCK_REALTIME, &now);
	target = timespec_add(now, NSEC_PER_SEC/2);
	clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &target, NULL);
	clock_gettime(CLOCK_REALTIME, &now);

	if (!in_order(target, now)) {
		printf("ERROR: hrtimer early expiration failure observed.\n");
		error_found = 1;
	}
}