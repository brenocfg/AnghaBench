#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;
union perf_event {TYPE_1__ header; } ;
typedef  int u32 ;
struct perf_mmap {int dummy; } ;
struct perf_evlist {int nr_mmaps; struct perf_mmap* overwrite_mmap; } ;

/* Variables and functions */
#define  PERF_RECORD_COMM 129 
#define  PERF_RECORD_SAMPLE 128 
 int TEST_FAIL ; 
 int TEST_OK ; 
 int /*<<< orphan*/  perf_mmap__read_done (struct perf_mmap*) ; 
 union perf_event* perf_mmap__read_event (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__read_init (struct perf_mmap*) ; 
 int /*<<< orphan*/  pr_err (char*,int const) ; 

__attribute__((used)) static int count_samples(struct perf_evlist *evlist, int *sample_count,
			 int *comm_count)
{
	int i;

	for (i = 0; i < evlist->nr_mmaps; i++) {
		struct perf_mmap *map = &evlist->overwrite_mmap[i];
		union perf_event *event;

		perf_mmap__read_init(map);
		while ((event = perf_mmap__read_event(map)) != NULL) {
			const u32 type = event->header.type;

			switch (type) {
			case PERF_RECORD_SAMPLE:
				(*sample_count)++;
				break;
			case PERF_RECORD_COMM:
				(*comm_count)++;
				break;
			default:
				pr_err("Unexpected record of type %d\n", type);
				return TEST_FAIL;
			}
		}
		perf_mmap__read_done(map);
	}
	return TEST_OK;
}