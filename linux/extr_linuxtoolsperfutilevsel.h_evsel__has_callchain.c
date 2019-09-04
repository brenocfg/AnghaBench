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
struct TYPE_2__ {int sample_type; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_SAMPLE_CALLCHAIN ; 

__attribute__((used)) static inline bool evsel__has_callchain(const struct perf_evsel *evsel)
{
	return (evsel->attr.sample_type & PERF_SAMPLE_CALLCHAIN) != 0;
}