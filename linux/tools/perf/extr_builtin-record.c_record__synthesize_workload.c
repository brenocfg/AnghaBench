#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tail_synthesize; int /*<<< orphan*/  sample_address; } ;
struct record {TYPE_3__ opts; TYPE_2__* session; int /*<<< orphan*/  tool; TYPE_5__* evlist; } ;
struct perf_thread_map {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  pid; } ;
struct TYPE_10__ {TYPE_4__ workload; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;
struct TYPE_7__ {TYPE_1__ machines; } ;

/* Variables and functions */
 int perf_event__synthesize_thread_map (int /*<<< orphan*/ *,struct perf_thread_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 
 int /*<<< orphan*/  process_synthesized_event ; 
 struct perf_thread_map* thread_map__new_by_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int record__synthesize_workload(struct record *rec, bool tail)
{
	int err;
	struct perf_thread_map *thread_map;

	if (rec->opts.tail_synthesize != tail)
		return 0;

	thread_map = thread_map__new_by_tid(rec->evlist->workload.pid);
	if (thread_map == NULL)
		return -1;

	err = perf_event__synthesize_thread_map(&rec->tool, thread_map,
						 process_synthesized_event,
						 &rec->session->machines.host,
						 rec->opts.sample_address);
	perf_thread_map__put(thread_map);
	return err;
}