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
typedef  int /*<<< orphan*/  u64 ;
struct intel_pt_queue {int switch_state; int next_tid; int on_heap; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  queue_nr; int /*<<< orphan*/  sync_switch; } ;
struct intel_pt {int /*<<< orphan*/  heap; int /*<<< orphan*/  tc; int /*<<< orphan*/  sync_switch; } ;
typedef  int pid_t ;

/* Variables and functions */
#define  INTEL_PT_SS_EXPECTING_SWITCH_EVENT 132 
#define  INTEL_PT_SS_EXPECTING_SWITCH_IP 131 
#define  INTEL_PT_SS_NOT_TRACING 130 
#define  INTEL_PT_SS_TRACING 129 
#define  INTEL_PT_SS_UNKNOWN 128 
 int auxtrace_heap__add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_pt_queue* intel_pt_cpu_to_ptq (struct intel_pt*,int) ; 
 int /*<<< orphan*/  intel_pt_log (char*,int) ; 
 int /*<<< orphan*/  perf_time_to_tsc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_pt_sync_switch(struct intel_pt *pt, int cpu, pid_t tid,
				u64 timestamp)
{
	struct intel_pt_queue *ptq;
	int err;

	if (!pt->sync_switch)
		return 1;

	ptq = intel_pt_cpu_to_ptq(pt, cpu);
	if (!ptq || !ptq->sync_switch)
		return 1;

	switch (ptq->switch_state) {
	case INTEL_PT_SS_NOT_TRACING:
		break;
	case INTEL_PT_SS_UNKNOWN:
	case INTEL_PT_SS_TRACING:
		ptq->next_tid = tid;
		ptq->switch_state = INTEL_PT_SS_EXPECTING_SWITCH_IP;
		return 0;
	case INTEL_PT_SS_EXPECTING_SWITCH_EVENT:
		if (!ptq->on_heap) {
			ptq->timestamp = perf_time_to_tsc(timestamp,
							  &pt->tc);
			err = auxtrace_heap__add(&pt->heap, ptq->queue_nr,
						 ptq->timestamp);
			if (err)
				return err;
			ptq->on_heap = true;
		}
		ptq->switch_state = INTEL_PT_SS_TRACING;
		break;
	case INTEL_PT_SS_EXPECTING_SWITCH_IP:
		intel_pt_log("ERROR: cpu %d expecting switch ip\n", cpu);
		break;
	default:
		break;
	}

	ptq->next_tid = -1;

	return 1;
}