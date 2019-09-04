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
struct TYPE_3__ {int sample_type; int sample_period; } ;
struct perf_evsel {char const* unit; int scale; TYPE_1__ attr; } ;
struct perf_event_attr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_RAW ; 
 int PERF_SAMPLE_TIME ; 
 int /*<<< orphan*/  perf_evsel__init (struct perf_evsel*,struct perf_event_attr*,int) ; 
 scalar_t__ perf_evsel__is_bpf_output (struct perf_evsel*) ; 
 scalar_t__ perf_evsel__is_clock (struct perf_evsel*) ; 
 TYPE_2__ perf_evsel__object ; 
 struct perf_evsel* zalloc (int /*<<< orphan*/ ) ; 

struct perf_evsel *perf_evsel__new_idx(struct perf_event_attr *attr, int idx)
{
	struct perf_evsel *evsel = zalloc(perf_evsel__object.size);

	if (!evsel)
		return NULL;
	perf_evsel__init(evsel, attr, idx);

	if (perf_evsel__is_bpf_output(evsel)) {
		evsel->attr.sample_type |= (PERF_SAMPLE_RAW | PERF_SAMPLE_TIME |
					    PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD),
		evsel->attr.sample_period = 1;
	}

	if (perf_evsel__is_clock(evsel)) {
		/*
		 * The evsel->unit points to static alias->unit
		 * so it's ok to use static string in here.
		 */
		static const char *unit = "msec";

		evsel->unit = unit;
		evsel->scale = 1e-6;
	}

	return evsel;
}