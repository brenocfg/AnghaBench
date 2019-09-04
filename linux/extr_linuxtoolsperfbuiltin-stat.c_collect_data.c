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
struct perf_evsel {scalar_t__ auto_merge_stats; scalar_t__ merged_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_all_aliases (struct perf_evsel*,void (*) (struct perf_evsel*,void*,int),void*) ; 
 scalar_t__ no_merge ; 
 int /*<<< orphan*/  uniquify_event_name (struct perf_evsel*) ; 

__attribute__((used)) static bool collect_data(struct perf_evsel *counter,
			    void (*cb)(struct perf_evsel *counter, void *data,
				       bool first),
			    void *data)
{
	if (counter->merged_stat)
		return false;
	cb(counter, data, true);
	if (no_merge)
		uniquify_event_name(counter);
	else if (counter->auto_merge_stats)
		collect_all_aliases(counter, cb, data);
	return true;
}