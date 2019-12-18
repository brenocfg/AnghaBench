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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int sample_type; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {int sample_size; TYPE_2__ core; } ;
typedef  enum perf_event_sample_format { ____Placeholder_perf_event_sample_format } perf_event_sample_format ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__calc_id_pos (struct evsel*) ; 

void __perf_evsel__reset_sample_bit(struct evsel *evsel,
				    enum perf_event_sample_format bit)
{
	if (evsel->core.attr.sample_type & bit) {
		evsel->core.attr.sample_type &= ~bit;
		evsel->sample_size -= sizeof(u64);
		perf_evsel__calc_id_pos(evsel);
	}
}