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
struct TYPE_2__ {int exclude_kernel; int exclude_hv; scalar_t__ type; int /*<<< orphan*/  pinned; int /*<<< orphan*/  precise_ip; int /*<<< orphan*/  exclude_user; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int nr_entries; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 
 struct perf_evsel* perf_evsel__next (struct perf_evsel*) ; 

__attribute__((used)) static int test__checkevent_pmu_events_mix(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__first(evlist);

	/* pmu-event:u */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->nr_entries);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->attr.pinned);

	/* cpu/pmu-event/u*/
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->attr.type);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->attr.pinned);

	return 0;
}