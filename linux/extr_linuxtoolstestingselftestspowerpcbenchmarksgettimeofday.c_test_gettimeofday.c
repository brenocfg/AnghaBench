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
struct timeval {double tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

__attribute__((used)) static int test_gettimeofday(void)
{
	int i;

	struct timeval tv_start, tv_end;

	gettimeofday(&tv_start, NULL);

	for(i = 0; i < 100000000; i++) {
		gettimeofday(&tv_end, NULL);
	}

	printf("time = %.6f\n", tv_end.tv_sec - tv_start.tv_sec + (tv_end.tv_usec - tv_start.tv_usec) * 1e-6);

	return 0;
}