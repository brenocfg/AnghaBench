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
struct TYPE_2__ {scalar_t__ type; int config; scalar_t__ sample_period; int sample_type; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int nr_entries; } ;

/* Variables and functions */
 int PERF_SAMPLE_TIME ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 int /*<<< orphan*/  evsel__has_callchain (struct perf_evsel*) ; 
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 
 struct perf_evsel* perf_evsel__next (struct perf_evsel*) ; 

__attribute__((used)) static int test__checkevent_pmu_partial_time_callgraph(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__first(evlist);

	/* cpu/config=1,call-graph=fp,time,period=100000/ */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->attr.type);
	TEST_ASSERT_VAL("wrong config",  1 == evsel->attr.config);
	/*
	 * The period, time and callgraph value gets configured
	 * within perf_evlist__config,
	 * while this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->attr.sample_period);
	TEST_ASSERT_VAL("wrong callgraph",  !evsel__has_callchain(evsel));
	TEST_ASSERT_VAL("wrong time",  !(PERF_SAMPLE_TIME & evsel->attr.sample_type));

	/* cpu/config=2,call-graph=no,time=0,period=2000/ */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->attr.type);
	TEST_ASSERT_VAL("wrong config",  2 == evsel->attr.config);
	/*
	 * The period, time and callgraph value gets configured
	 * within perf_evlist__config,
	 * while this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->attr.sample_period);
	TEST_ASSERT_VAL("wrong callgraph",  !evsel__has_callchain(evsel));
	TEST_ASSERT_VAL("wrong time",  !(PERF_SAMPLE_TIME & evsel->attr.sample_type));

	return 0;
}