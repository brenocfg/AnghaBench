#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* array; } ;
struct TYPE_5__ {scalar_t__ type; } ;
union perf_event {TYPE_2__ sample; TYPE_1__ header; } ;
typedef  int u64 ;
struct perf_sample {unsigned long long time; } ;
struct TYPE_8__ {int sample_type; int /*<<< orphan*/  sample_id_all; } ;
struct TYPE_7__ {TYPE_4__ attr; } ;
struct evsel {int /*<<< orphan*/  sample_size; TYPE_3__ core; } ;
typedef  int __u64 ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ PERF_RECORD_SAMPLE ; 
 int PERF_SAMPLE_IDENTIFIER ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 scalar_t__ perf_event__check_size (union perf_event*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evsel__parse_id_sample (struct evsel*,union perf_event*,struct perf_sample*) ; 

int perf_evsel__parse_sample_timestamp(struct evsel *evsel,
				       union perf_event *event,
				       u64 *timestamp)
{
	u64 type = evsel->core.attr.sample_type;
	const __u64 *array;

	if (!(type & PERF_SAMPLE_TIME))
		return -1;

	if (event->header.type != PERF_RECORD_SAMPLE) {
		struct perf_sample data = {
			.time = -1ULL,
		};

		if (!evsel->core.attr.sample_id_all)
			return -1;
		if (perf_evsel__parse_id_sample(evsel, event, &data))
			return -1;

		*timestamp = data.time;
		return 0;
	}

	array = event->sample.array;

	if (perf_event__check_size(event, evsel->sample_size))
		return -EFAULT;

	if (type & PERF_SAMPLE_IDENTIFIER)
		array++;

	if (type & PERF_SAMPLE_IP)
		array++;

	if (type & PERF_SAMPLE_TID)
		array++;

	if (type & PERF_SAMPLE_TIME)
		*timestamp = *array;

	return 0;
}