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
struct evsel {int dummy; } ;

/* Variables and functions */
 int perf_evsel__append_filter (struct evsel*,char*,char const*) ; 

int perf_evsel__append_tp_filter(struct evsel *evsel, const char *filter)
{
	return perf_evsel__append_filter(evsel, "(%s) && (%s)", filter);
}