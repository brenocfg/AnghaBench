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
struct TYPE_2__ {scalar_t__ type; scalar_t__ config; scalar_t__ bp_type; scalar_t__ bp_len; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int nr_entries; } ;

/* Variables and functions */
 scalar_t__ HW_BREAKPOINT_LEN_4 ; 
 scalar_t__ HW_BREAKPOINT_R ; 
 scalar_t__ PERF_TYPE_BREAKPOINT ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 

__attribute__((used)) static int test__checkevent_breakpoint_r(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->nr_entries);
	TEST_ASSERT_VAL("wrong type",
			PERF_TYPE_BREAKPOINT == evsel->attr.type);
	TEST_ASSERT_VAL("wrong config", 0 == evsel->attr.config);
	TEST_ASSERT_VAL("wrong bp_type",
			HW_BREAKPOINT_R == evsel->attr.bp_type);
	TEST_ASSERT_VAL("wrong bp_len",
			HW_BREAKPOINT_LEN_4 == evsel->attr.bp_len);
	return 0;
}