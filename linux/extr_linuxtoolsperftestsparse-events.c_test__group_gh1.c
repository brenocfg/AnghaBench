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
struct TYPE_2__ {scalar_t__ type; scalar_t__ config; int exclude_guest; int /*<<< orphan*/  precise_ip; int /*<<< orphan*/  exclude_host; int /*<<< orphan*/  exclude_hv; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  exclude_user; } ;
struct perf_evsel {int nr_members; struct perf_evsel* leader; TYPE_1__ attr; int /*<<< orphan*/  group_name; } ;
struct perf_evlist {int nr_entries; int nr_groups; } ;

/* Variables and functions */
 scalar_t__ PERF_COUNT_HW_CACHE_MISSES ; 
 scalar_t__ PERF_COUNT_HW_CPU_CYCLES ; 
 scalar_t__ PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 
 int perf_evsel__group_idx (struct perf_evsel*) ; 
 int perf_evsel__is_group_leader (struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__next (struct perf_evsel*) ; 

__attribute__((used)) static int test__group_gh1(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel, *leader;

	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 1 == evlist->nr_groups);

	/* cycles + :H group modifier */
	evsel = leader = perf_evlist__first(evlist);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", evsel->attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->attr.precise_ip);
	TEST_ASSERT_VAL("wrong group name", !evsel->group_name);
	TEST_ASSERT_VAL("wrong leader", perf_evsel__is_group_leader(evsel));
	TEST_ASSERT_VAL("wrong nr_members", evsel->nr_members == 2);
	TEST_ASSERT_VAL("wrong group_idx", perf_evsel__group_idx(evsel) == 0);

	/* cache-misses:G + :H group modifier */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CACHE_MISSES == evsel->attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->attr.exclude_hv);
	TEST_ASSERT_VAL("wrong exclude guest", !evsel->attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->attr.exclude_host);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->attr.precise_ip);
	TEST_ASSERT_VAL("wrong leader", evsel->leader == leader);
	TEST_ASSERT_VAL("wrong group_idx", perf_evsel__group_idx(evsel) == 1);

	return 0;
}