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
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_RAW ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 long long diff_timespec (struct timespec,struct timespec) ; 
 struct timespec nsec_to_ts (long long) ; 
 int ts_to_nsec (struct timespec) ; 

void get_monotonic_and_raw(struct timespec *mon, struct timespec *raw)
{
	struct timespec start, mid, end;
	long long diff = 0, tmp;
	int i;

	clock_gettime(CLOCK_MONOTONIC, mon);
	clock_gettime(CLOCK_MONOTONIC_RAW, raw);

	/* Try to get a more tightly bound pairing */
	for (i = 0; i < 3; i++) {
		long long newdiff;

		clock_gettime(CLOCK_MONOTONIC, &start);
		clock_gettime(CLOCK_MONOTONIC_RAW, &mid);
		clock_gettime(CLOCK_MONOTONIC, &end);

		newdiff = diff_timespec(start, end);
		if (diff == 0 || newdiff < diff) {
			diff = newdiff;
			*raw = mid;
			tmp = (ts_to_nsec(start) + ts_to_nsec(end))/2;
			*mon = nsec_to_ts(tmp);
		}
	}
}