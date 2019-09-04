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
struct perf_evlist {scalar_t__ nr_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 scalar_t__ count_tracepoints () ; 
 int test__checkevent_tracepoint_multi (struct perf_evlist*) ; 

__attribute__((used)) static int test__all_tracepoints(struct perf_evlist *evlist)
{
	TEST_ASSERT_VAL("wrong events count",
			count_tracepoints() == evlist->nr_entries);

	return test__checkevent_tracepoint_multi(evlist);
}