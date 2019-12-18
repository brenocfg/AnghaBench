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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pt_regs {int dummy; } ;
struct TYPE_9__ {scalar_t__ regs; } ;
struct TYPE_8__ {scalar_t__ regs; } ;
struct perf_sample_data {int stack_user_size; int /*<<< orphan*/  addr; int /*<<< orphan*/  phys_addr; TYPE_4__ regs_intr; TYPE_3__ regs_user; int /*<<< orphan*/  regs_user_copy; TYPE_1__* br_stack; struct perf_raw_record* raw; TYPE_5__* callchain; int /*<<< orphan*/  ip; } ;
struct perf_raw_frag {scalar_t__ pad; struct perf_raw_frag* next; scalar_t__ size; } ;
struct perf_raw_record {int size; struct perf_raw_frag frag; } ;
struct perf_event_header {scalar_t__ size; int /*<<< orphan*/  misc; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int sample_type; int sample_regs_user; int sample_stack_user; int sample_regs_intr; } ;
struct perf_event {TYPE_2__ attr; scalar_t__ header_size; } ;
struct perf_branch_entry {int dummy; } ;
struct TYPE_10__ {scalar_t__ nr; } ;
struct TYPE_6__ {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_PHYS_ADDR ; 
 int PERF_SAMPLE_RAW ; 
 int PERF_SAMPLE_REGS_INTR ; 
 int PERF_SAMPLE_REGS_USER ; 
 int PERF_SAMPLE_STACK_USER ; 
 int __PERF_SAMPLE_CALLCHAIN_EARLY ; 
 int /*<<< orphan*/  __perf_event_header__init_id (struct perf_event_header*,struct perf_sample_data*,struct perf_event*) ; 
 int hweight64 (int) ; 
 TYPE_5__* perf_callchain (struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_misc_flags (struct pt_regs*) ; 
 scalar_t__ perf_raw_frag_last (struct perf_raw_frag*) ; 
 int /*<<< orphan*/  perf_sample_regs_intr (TYPE_4__*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_regs_user (TYPE_3__*,struct pt_regs*,int /*<<< orphan*/ *) ; 
 int perf_sample_ustack_size (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  perf_virt_to_phys (int /*<<< orphan*/ ) ; 
 int round_up (scalar_t__,int) ; 

void perf_prepare_sample(struct perf_event_header *header,
			 struct perf_sample_data *data,
			 struct perf_event *event,
			 struct pt_regs *regs)
{
	u64 sample_type = event->attr.sample_type;

	header->type = PERF_RECORD_SAMPLE;
	header->size = sizeof(*header) + event->header_size;

	header->misc = 0;
	header->misc |= perf_misc_flags(regs);

	__perf_event_header__init_id(header, data, event);

	if (sample_type & PERF_SAMPLE_IP)
		data->ip = perf_instruction_pointer(regs);

	if (sample_type & PERF_SAMPLE_CALLCHAIN) {
		int size = 1;

		if (!(sample_type & __PERF_SAMPLE_CALLCHAIN_EARLY))
			data->callchain = perf_callchain(event, regs);

		size += data->callchain->nr;

		header->size += size * sizeof(u64);
	}

	if (sample_type & PERF_SAMPLE_RAW) {
		struct perf_raw_record *raw = data->raw;
		int size;

		if (raw) {
			struct perf_raw_frag *frag = &raw->frag;
			u32 sum = 0;

			do {
				sum += frag->size;
				if (perf_raw_frag_last(frag))
					break;
				frag = frag->next;
			} while (1);

			size = round_up(sum + sizeof(u32), sizeof(u64));
			raw->size = size - sizeof(u32);
			frag->pad = raw->size - sum;
		} else {
			size = sizeof(u64);
		}

		header->size += size;
	}

	if (sample_type & PERF_SAMPLE_BRANCH_STACK) {
		int size = sizeof(u64); /* nr */
		if (data->br_stack) {
			size += data->br_stack->nr
			      * sizeof(struct perf_branch_entry);
		}
		header->size += size;
	}

	if (sample_type & (PERF_SAMPLE_REGS_USER | PERF_SAMPLE_STACK_USER))
		perf_sample_regs_user(&data->regs_user, regs,
				      &data->regs_user_copy);

	if (sample_type & PERF_SAMPLE_REGS_USER) {
		/* regs dump ABI info */
		int size = sizeof(u64);

		if (data->regs_user.regs) {
			u64 mask = event->attr.sample_regs_user;
			size += hweight64(mask) * sizeof(u64);
		}

		header->size += size;
	}

	if (sample_type & PERF_SAMPLE_STACK_USER) {
		/*
		 * Either we need PERF_SAMPLE_STACK_USER bit to be always
		 * processed as the last one or have additional check added
		 * in case new sample type is added, because we could eat
		 * up the rest of the sample size.
		 */
		u16 stack_size = event->attr.sample_stack_user;
		u16 size = sizeof(u64);

		stack_size = perf_sample_ustack_size(stack_size, header->size,
						     data->regs_user.regs);

		/*
		 * If there is something to dump, add space for the dump
		 * itself and for the field that tells the dynamic size,
		 * which is how many have been actually dumped.
		 */
		if (stack_size)
			size += sizeof(u64) + stack_size;

		data->stack_user_size = stack_size;
		header->size += size;
	}

	if (sample_type & PERF_SAMPLE_REGS_INTR) {
		/* regs dump ABI info */
		int size = sizeof(u64);

		perf_sample_regs_intr(&data->regs_intr, regs);

		if (data->regs_intr.regs) {
			u64 mask = event->attr.sample_regs_intr;

			size += hweight64(mask) * sizeof(u64);
		}

		header->size += size;
	}

	if (sample_type & PERF_SAMPLE_PHYS_ADDR)
		data->phys_addr = perf_virt_to_phys(data->addr);
}