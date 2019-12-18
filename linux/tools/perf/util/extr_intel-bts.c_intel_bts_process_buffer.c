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
typedef  int u32 ;
struct thread {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
struct intel_bts_queue {int sample_flags; TYPE_3__ intel_pt_insn; int /*<<< orphan*/  cpu; TYPE_2__* bts; } ;
struct branch {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
struct auxtrace_buffer {size_t use_size; size_t size; scalar_t__ buffer_nr; struct branch* data; struct branch* use_data; } ;
struct TYPE_4__ {scalar_t__ thread_stack; } ;
struct TYPE_5__ {int branches_filter; TYPE_1__ synth_opts; int /*<<< orphan*/  sample_branches; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_bts_get_branch_type (struct intel_bts_queue*,struct branch*) ; 
 int intel_bts_synth_branch_sample (struct intel_bts_queue*,struct branch*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_stack__event (struct thread*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int intel_bts_process_buffer(struct intel_bts_queue *btsq,
				    struct auxtrace_buffer *buffer,
				    struct thread *thread)
{
	struct branch *branch;
	size_t sz, bsz = sizeof(struct branch);
	u32 filter = btsq->bts->branches_filter;
	int err = 0;

	if (buffer->use_data) {
		sz = buffer->use_size;
		branch = buffer->use_data;
	} else {
		sz = buffer->size;
		branch = buffer->data;
	}

	if (!btsq->bts->sample_branches)
		return 0;

	for (; sz > bsz; branch += 1, sz -= bsz) {
		if (!branch->from && !branch->to)
			continue;
		intel_bts_get_branch_type(btsq, branch);
		if (btsq->bts->synth_opts.thread_stack)
			thread_stack__event(thread, btsq->cpu, btsq->sample_flags,
					    le64_to_cpu(branch->from),
					    le64_to_cpu(branch->to),
					    btsq->intel_pt_insn.length,
					    buffer->buffer_nr + 1);
		if (filter && !(filter & btsq->sample_flags))
			continue;
		err = intel_bts_synth_branch_sample(btsq, branch);
		if (err)
			break;
	}
	return err;
}