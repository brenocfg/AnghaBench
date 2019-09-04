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
struct TYPE_2__ {int branch_sample_type; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_SAMPLE_BRANCH_CALL_STACK ; 

__attribute__((used)) static inline bool perf_evsel__has_branch_callstack(const struct perf_evsel *evsel)
{
	return evsel->attr.branch_sample_type & PERF_SAMPLE_BRANCH_CALL_STACK;
}