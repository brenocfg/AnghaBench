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
struct TYPE_3__ {int size; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ header; } ;
union perf_event {TYPE_2__ sample; } ;
struct perf_sample {int /*<<< orphan*/  insn; int /*<<< orphan*/  insn_len; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct perf_event_header {int dummy; } ;
struct intel_pt_queue {int /*<<< orphan*/  insn; int /*<<< orphan*/  insn_len; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_INSN_BUF_SZ ; 
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pt_prep_a_sample(struct intel_pt_queue *ptq,
				   union perf_event *event,
				   struct perf_sample *sample)
{
	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.size = sizeof(struct perf_event_header);

	sample->pid = ptq->pid;
	sample->tid = ptq->tid;
	sample->cpu = ptq->cpu;
	sample->insn_len = ptq->insn_len;
	memcpy(sample->insn, ptq->insn, INTEL_PT_INSN_BUF_SZ);
}