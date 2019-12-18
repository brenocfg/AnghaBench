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
struct perf_stat_config {scalar_t__ no_merge; } ;
struct evsel {scalar_t__ auto_merge_stats; scalar_t__ merged_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_all_aliases (struct perf_stat_config*,struct evsel*,void (*) (struct perf_stat_config*,struct evsel*,void*,int),void*) ; 
 int /*<<< orphan*/  uniquify_event_name (struct evsel*) ; 

__attribute__((used)) static bool collect_data(struct perf_stat_config *config, struct evsel *counter,
			    void (*cb)(struct perf_stat_config *config, struct evsel *counter, void *data,
				       bool first),
			    void *data)
{
	if (counter->merged_stat)
		return false;
	cb(config, counter, data, true);
	if (config->no_merge)
		uniquify_event_name(counter);
	else if (counter->auto_merge_stats)
		collect_all_aliases(config, counter, cb, data);
	return true;
}