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
union u64_swap {void** val32; void* val64; } ;
struct TYPE_8__ {int size; } ;
struct TYPE_7__ {void** array; } ;
union perf_event {TYPE_4__ header; TYPE_3__ sample; } ;
typedef  int u64 ;
struct perf_sample {void* tid; void* pid; void* time; void* id; void* stream_id; void* cpu; } ;
struct TYPE_5__ {int sample_type; } ;
struct TYPE_6__ {TYPE_1__ attr; } ;
struct evsel {int needs_swap; TYPE_2__ core; } ;
typedef  void* __u64 ;

/* Variables and functions */
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_ID ; 
 int PERF_SAMPLE_IDENTIFIER ; 
 int PERF_SAMPLE_STREAM_ID ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 void* bswap_32 (void*) ; 
 void* bswap_64 (void*) ; 

__attribute__((used)) static int perf_evsel__parse_id_sample(const struct evsel *evsel,
				       const union perf_event *event,
				       struct perf_sample *sample)
{
	u64 type = evsel->core.attr.sample_type;
	const __u64 *array = event->sample.array;
	bool swapped = evsel->needs_swap;
	union u64_swap u;

	array += ((event->header.size -
		   sizeof(event->header)) / sizeof(u64)) - 1;

	if (type & PERF_SAMPLE_IDENTIFIER) {
		sample->id = *array;
		array--;
	}

	if (type & PERF_SAMPLE_CPU) {
		u.val64 = *array;
		if (swapped) {
			/* undo swap of u64, then swap on individual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
		}

		sample->cpu = u.val32[0];
		array--;
	}

	if (type & PERF_SAMPLE_STREAM_ID) {
		sample->stream_id = *array;
		array--;
	}

	if (type & PERF_SAMPLE_ID) {
		sample->id = *array;
		array--;
	}

	if (type & PERF_SAMPLE_TIME) {
		sample->time = *array;
		array--;
	}

	if (type & PERF_SAMPLE_TID) {
		u.val64 = *array;
		if (swapped) {
			/* undo swap of u64, then swap on individual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
			u.val32[1] = bswap_32(u.val32[1]);
		}

		sample->pid = u.val32[0];
		sample->tid = u.val32[1];
		array--;
	}

	return 0;
}