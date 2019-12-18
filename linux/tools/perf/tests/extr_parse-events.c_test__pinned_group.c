#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; scalar_t__ config; int pinned; } ;
struct TYPE_6__ {TYPE_2__ attr; } ;
struct evsel {TYPE_3__ core; struct evsel* leader; int /*<<< orphan*/  group_name; } ;
struct TYPE_4__ {int nr_entries; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ PERF_COUNT_HW_BRANCH_MISSES ; 
 scalar_t__ PERF_COUNT_HW_CACHE_MISSES ; 
 scalar_t__ PERF_COUNT_HW_CPU_CYCLES ; 
 scalar_t__ PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 struct evsel* perf_evsel__next (struct evsel*) ; 

__attribute__((used)) static int test__pinned_group(struct evlist *evlist)
{
	struct evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);

	/* cycles - group leader */
	evsel = leader = evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong pinned", evsel->core.attr.pinned);

	/* cache-misses - can not be pinned, but will go on with the leader */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);

	/* branch-misses - ditto */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_BRANCH_MISSES == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);

	return 0;
}