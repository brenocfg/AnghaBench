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
struct timespec {unsigned long long tv_sec; unsigned long long tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 float NR_LOOPS ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  do_null_syscall (float) ; 
 int /*<<< orphan*/  get_proc_frequency () ; 
 unsigned long mftb () ; 
 int /*<<< orphan*/  printf (char*,float,float) ; 
 float timebase_multiplier ; 

int main(void)
{
	unsigned long tb_start, tb_now;
	struct timespec tv_start, tv_now;
	unsigned long long elapsed_ns, elapsed_tb;

	get_proc_frequency();

	clock_gettime(CLOCK_MONOTONIC, &tv_start);
	tb_start = mftb();

	do_null_syscall(NR_LOOPS);

	clock_gettime(CLOCK_MONOTONIC, &tv_now);
	tb_now = mftb();

	elapsed_ns = (tv_now.tv_sec - tv_start.tv_sec) * 1000000000ULL +
			(tv_now.tv_nsec - tv_start.tv_nsec);
	elapsed_tb = tb_now - tb_start;

	printf("%10.2f ns %10.2f cycles\n", (float)elapsed_ns / NR_LOOPS,
			(float)elapsed_tb * timebase_multiplier / NR_LOOPS);

	return 0;
}