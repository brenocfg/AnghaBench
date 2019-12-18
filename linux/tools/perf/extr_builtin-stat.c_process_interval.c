#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_2__ {int interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  INTERVAL ; 
 int NSEC_PER_SEC ; 
 scalar_t__ STAT_RECORD ; 
 scalar_t__ WRITE_STAT_ROUND_EVENT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  diff_timespec (struct timespec*,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_counters (struct timespec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_counters (struct timespec*) ; 
 int /*<<< orphan*/  ref_time ; 
 TYPE_1__ stat_config ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  walltime_nsecs_stats ; 

__attribute__((used)) static void process_interval(void)
{
	struct timespec ts, rs;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	diff_timespec(&rs, &ts, &ref_time);

	read_counters(&rs);

	if (STAT_RECORD) {
		if (WRITE_STAT_ROUND_EVENT(rs.tv_sec * NSEC_PER_SEC + rs.tv_nsec, INTERVAL))
			pr_err("failed to write stat round event\n");
	}

	init_stats(&walltime_nsecs_stats);
	update_stats(&walltime_nsecs_stats, stat_config.interval * 1000000);
	print_counters(&rs, 0, NULL);
}