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
struct timeval {long long tv_usec; long long tv_sec; } ;

/* Variables and functions */
 long long DELAY ; 
 long long USECS_PER_SEC ; 
 long long abs (long long) ; 
 int /*<<< orphan*/  printf (char*,long long) ; 

__attribute__((used)) static int check_diff(struct timeval start, struct timeval end)
{
	long long diff;

	diff = end.tv_usec - start.tv_usec;
	diff += (end.tv_sec - start.tv_sec) * USECS_PER_SEC;

	if (abs(diff - DELAY * USECS_PER_SEC) > USECS_PER_SEC / 2) {
		printf("Diff too high: %lld..", diff);
		return -1;
	}

	return 0;
}