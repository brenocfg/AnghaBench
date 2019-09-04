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
struct TYPE_2__ {scalar_t__ type; int exclude_kernel; int exclude_hv; int /*<<< orphan*/  pinned; int /*<<< orphan*/  precise_ip; int /*<<< orphan*/  exclude_user; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int nr_entries; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 

__attribute__((used)) static int test__checkevent_pmu_events(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->nr_entries);
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