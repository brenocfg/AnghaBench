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
struct TYPE_6__ {int size; int /*<<< orphan*/  misc; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_2__ header; } ;
union perf_event {TYPE_3__ sample; } ;
typedef  void* u64 ;
struct perf_sample {int insn_len; int /*<<< orphan*/  branch_stack; int /*<<< orphan*/  cpumode; scalar_t__ flags; int /*<<< orphan*/  cpu; void* period; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  id; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; void* ip; } ;
struct perf_event_header {int dummy; } ;
struct cs_etm_queue {int /*<<< orphan*/  last_branch; TYPE_1__* packet; struct cs_etm_auxtrace* etm; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; union perf_event* event_buf; } ;
struct TYPE_8__ {scalar_t__ last_branch; scalar_t__ inject; } ;
struct cs_etm_auxtrace {TYPE_4__ synth_opts; int /*<<< orphan*/  session; int /*<<< orphan*/  instructions_sample_type; int /*<<< orphan*/  instructions_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  cs_etm__copy_last_branch_rb (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  cs_etm__cpu_mode (struct cs_etm_queue*,void*) ; 
 int cs_etm__inject_event (union perf_event*,struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm__reset_last_branch_rb (struct cs_etm_queue*) ; 
 int perf_session__deliver_synth_event (int /*<<< orphan*/ ,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int cs_etm__synth_instruction_sample(struct cs_etm_queue *etmq,
					    u64 addr, u64 period)
{
	int ret = 0;
	struct cs_etm_auxtrace *etm = etmq->etm;
	union perf_event *event = etmq->event_buf;
	struct perf_sample sample = {.ip = 0,};

	event->sample.header.type = PERF_RECORD_SAMPLE;
	event->sample.header.misc = cs_etm__cpu_mode(etmq, addr);
	event->sample.header.size = sizeof(struct perf_event_header);

	sample.ip = addr;
	sample.pid = etmq->pid;
	sample.tid = etmq->tid;
	sample.id = etmq->etm->instructions_id;
	sample.stream_id = etmq->etm->instructions_id;
	sample.period = period;
	sample.cpu = etmq->packet->cpu;
	sample.flags = 0;
	sample.insn_len = 1;
	sample.cpumode = event->sample.header.misc;

	if (etm->synth_opts.last_branch) {
		cs_etm__copy_last_branch_rb(etmq);
		sample.branch_stack = etmq->last_branch;
	}

	if (etm->synth_opts.inject) {
		ret = cs_etm__inject_event(event, &sample,
					   etm->instructions_sample_type);
		if (ret)
			return ret;
	}

	ret = perf_session__deliver_synth_event(etm->session, event, &sample);

	if (ret)
		pr_err(
			"CS ETM Trace: failed to deliver instruction event, error %d\n",
			ret);

	if (etm->synth_opts.last_branch)
		cs_etm__reset_last_branch_rb(etmq);

	return ret;
}