#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct TYPE_3__ {scalar_t__ is_pipe; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ STAT_RECORD ; 
 int /*<<< orphan*/  evsel_list ; 
 int /*<<< orphan*/  perf_evlist__print_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*,int,char const**) ; 
 TYPE_2__ perf_stat ; 
 int /*<<< orphan*/  stat_config ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static void print_counters(struct timespec *ts, int argc, const char **argv)
{
	/* Do not print anything if we record to the pipe. */
	if (STAT_RECORD && perf_stat.data.is_pipe)
		return;

	perf_evlist__print_counters(evsel_list, &stat_config, &target,
				    ts, argc, argv);
}