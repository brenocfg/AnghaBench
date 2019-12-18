#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nr_members; } ;
struct evsel {TYPE_1__ core; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_group; } ;

/* Variables and functions */
 scalar_t__ perf_evsel__is_group_leader (struct evsel*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static inline bool perf_evsel__is_group_event(struct evsel *evsel)
{
	if (!symbol_conf.event_group)
		return false;

	return perf_evsel__is_group_leader(evsel) && evsel->core.nr_members > 1;
}