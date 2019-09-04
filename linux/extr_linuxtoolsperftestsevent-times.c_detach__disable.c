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
struct perf_evsel {int dummy; } ;
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 struct perf_evsel* perf_evlist__last (struct perf_evlist*) ; 
 int perf_evsel__enable (struct perf_evsel*) ; 

__attribute__((used)) static int detach__disable(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__last(evlist);

	return perf_evsel__enable(evsel);
}