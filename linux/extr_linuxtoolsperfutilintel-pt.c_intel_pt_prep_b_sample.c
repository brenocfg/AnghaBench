#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int /*<<< orphan*/  misc; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_2__ header; } ;
union perf_event {TYPE_3__ sample; } ;
struct perf_sample {int period; int /*<<< orphan*/  cpumode; int /*<<< orphan*/  insn; int /*<<< orphan*/  insn_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  cpu; int /*<<< orphan*/  addr; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  ip; int /*<<< orphan*/  time; } ;
struct perf_event_header {int dummy; } ;
struct intel_pt_queue {int /*<<< orphan*/  insn; int /*<<< orphan*/  insn_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  cpu; TYPE_1__* state; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  timestamp; } ;
struct intel_pt {int /*<<< orphan*/  tc; int /*<<< orphan*/  timeless_decoding; } ;
struct TYPE_4__ {int /*<<< orphan*/  to_ip; int /*<<< orphan*/  from_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_INSN_BUF_SZ ; 
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  intel_pt_cpumode (struct intel_pt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc_to_perf_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pt_prep_b_sample(struct intel_pt *pt,
				   struct intel_pt_queue *ptq,
				   union perf_event *event,
				   struct perf_sample *sample)
{
	if (!pt->timeless_decoding)
		sample->time = tsc_to_perf_time(ptq->timestamp, &pt->tc);

	sample->ip = ptq->state->from_ip;
	sample->cpumode = intel_pt_cpumode(pt, sample->ip);
	sample->pid = ptq->pid;
	sample->tid = ptq->tid;
	sample->addr = ptq->state->to_ip;
	sample->period = 1;
	sample->cpu = ptq->cpu;
	sample->flags = ptq->flags;
	sample->insn_len = ptq->insn_len;
	memcpy(sample->insn, ptq->insn, INTEL_PT_INSN_BUF_SZ);

	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.misc = sample->cpumode;
	event->sample.header.size = sizeof(struct perf_event_header);
}