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
struct perf_sample {int dummy; } ;
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 char* perf_evsel__rawptr (struct perf_evsel*,struct perf_sample*,char const*) ; 

__attribute__((used)) static inline char *perf_evsel__strval(struct perf_evsel *evsel,
				       struct perf_sample *sample,
				       const char *name)
{
	return perf_evsel__rawptr(evsel, sample, name);
}