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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct seq_file {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int ktime_get_ns () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int udelay_test_single(struct seq_file *s, int usecs, uint32_t iters)
{
	int min = 0, max = 0, fail_count = 0;
	uint64_t sum = 0;
	uint64_t avg;
	int i;
	/* Allow udelay to be up to 0.5% fast */
	int allowed_error_ns = usecs * 5;

	for (i = 0; i < iters; ++i) {
		s64 kt1, kt2;
		int time_passed;

		kt1 = ktime_get_ns();
		udelay(usecs);
		kt2 = ktime_get_ns();
		time_passed = kt2 - kt1;

		if (i == 0 || time_passed < min)
			min = time_passed;
		if (i == 0 || time_passed > max)
			max = time_passed;
		if ((time_passed + allowed_error_ns) / 1000 < usecs)
			++fail_count;
		WARN_ON(time_passed < 0);
		sum += time_passed;
	}

	avg = sum;
	do_div(avg, iters);
	seq_printf(s, "%d usecs x %d: exp=%d allowed=%d min=%d avg=%lld max=%d",
			usecs, iters, usecs * 1000,
			(usecs * 1000) - allowed_error_ns, min, avg, max);
	if (fail_count)
		seq_printf(s, " FAIL=%d", fail_count);
	seq_puts(s, "\n");

	return 0;
}