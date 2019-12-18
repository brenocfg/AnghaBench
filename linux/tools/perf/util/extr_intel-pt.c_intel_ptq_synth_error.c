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
struct intel_pt_state {int /*<<< orphan*/  from_ip; int /*<<< orphan*/  err; } ;
struct intel_pt_queue {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  cpu; int /*<<< orphan*/  timestamp; struct intel_pt* pt; } ;
struct intel_pt {int /*<<< orphan*/  tc; scalar_t__ timeless_decoding; } ;

/* Variables and functions */
 int intel_pt_synth_error (struct intel_pt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc_to_perf_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_ptq_synth_error(struct intel_pt_queue *ptq,
				 const struct intel_pt_state *state)
{
	struct intel_pt *pt = ptq->pt;
	u64 tm = ptq->timestamp;

	tm = pt->timeless_decoding ? 0 : tsc_to_perf_time(tm, &pt->tc);

	return intel_pt_synth_error(pt, state->err, ptq->cpu, ptq->pid,
				    ptq->tid, state->from_ip, tm);
}