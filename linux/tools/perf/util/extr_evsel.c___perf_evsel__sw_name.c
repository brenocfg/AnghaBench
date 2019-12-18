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
typedef  size_t u64 ;

/* Variables and functions */
 size_t PERF_COUNT_SW_MAX ; 
 char const** perf_evsel__sw_names ; 

__attribute__((used)) static const char *__perf_evsel__sw_name(u64 config)
{
	if (config < PERF_COUNT_SW_MAX && perf_evsel__sw_names[config])
		return perf_evsel__sw_names[config];
	return "unknown-software";
}