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
struct TYPE_6__ {scalar_t__ type; scalar_t__ sample_type; int sample_period; } ;
struct TYPE_5__ {TYPE_3__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct TYPE_4__ {int nr_entries; } ;
struct evlist {scalar_t__ nr_groups; TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ PERF_TP_SAMPLE_TYPE ; 
 scalar_t__ PERF_TYPE_TRACEPOINT ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 

__attribute__((used)) static int test__checkevent_tracepoint(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong number of groups", 0 == evlist->nr_groups);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_TRACEPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong sample_type",
		PERF_TP_SAMPLE_TYPE == evsel->core.attr.sample_type);
	TEST_ASSERT_VAL("wrong sample_period", 1 == evsel->core.attr.sample_period);
	return 0;
}