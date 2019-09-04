#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
union u64_swap {size_t* val32; int val64; } ;
struct TYPE_10__ {int* array; } ;
union perf_event {TYPE_2__ sample; } ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sample_read_value {int dummy; } ;
struct TYPE_9__ {size_t abi; TYPE_8__* regs; int /*<<< orphan*/  mask; } ;
struct TYPE_15__ {size_t size; TYPE_8__* data; } ;
struct TYPE_14__ {TYPE_8__* regs; int /*<<< orphan*/  mask; scalar_t__ abi; } ;
struct TYPE_12__ {int value; int id; } ;
struct TYPE_11__ {int nr; TYPE_8__* values; } ;
struct TYPE_13__ {int time_enabled; int time_running; TYPE_4__ one; TYPE_3__ group; } ;
struct perf_sample {int id; int ip; size_t pid; size_t tid; int time; int addr; int stream_id; size_t cpu; int period; size_t raw_size; int weight; int data_src; int transaction; int phys_addr; TYPE_1__ intr_regs; TYPE_7__ user_stack; TYPE_6__ user_regs; TYPE_8__* branch_stack; TYPE_8__* raw_data; TYPE_8__* callchain; TYPE_5__ read; } ;
struct branch_entry {int dummy; } ;
struct TYPE_16__ {int nr; } ;

/* Variables and functions */
 int PERF_FORMAT_GROUP ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int PERF_SAMPLE_ADDR ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_DATA_SRC ; 
 int PERF_SAMPLE_ID ; 
 int PERF_SAMPLE_IDENTIFIER ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_PHYS_ADDR ; 
 int PERF_SAMPLE_RAW ; 
 int PERF_SAMPLE_READ ; 
 int PERF_SAMPLE_REGS_INTR ; 
 int PERF_SAMPLE_REGS_USER ; 
 int PERF_SAMPLE_STACK_USER ; 
 int PERF_SAMPLE_STREAM_ID ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 int PERF_SAMPLE_TRANSACTION ; 
 int PERF_SAMPLE_WEIGHT ; 
 int hweight_long (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_8__*,size_t) ; 

int perf_event__synthesize_sample(union perf_event *event, u64 type,
				  u64 read_format,
				  const struct perf_sample *sample)
{
	u64 *array;
	size_t sz;
	/*
	 * used for cross-endian analysis. See git commit 65014ab3
	 * for why this goofiness is needed.
	 */
	union u64_swap u;

	array = event->sample.array;

	if (type & PERF_SAMPLE_IDENTIFIER) {
		*array = sample->id;
		array++;
	}

	if (type & PERF_SAMPLE_IP) {
		*array = sample->ip;
		array++;
	}

	if (type & PERF_SAMPLE_TID) {
		u.val32[0] = sample->pid;
		u.val32[1] = sample->tid;
		*array = u.val64;
		array++;
	}

	if (type & PERF_SAMPLE_TIME) {
		*array = sample->time;
		array++;
	}

	if (type & PERF_SAMPLE_ADDR) {
		*array = sample->addr;
		array++;
	}

	if (type & PERF_SAMPLE_ID) {
		*array = sample->id;
		array++;
	}

	if (type & PERF_SAMPLE_STREAM_ID) {
		*array = sample->stream_id;
		array++;
	}

	if (type & PERF_SAMPLE_CPU) {
		u.val32[0] = sample->cpu;
		u.val32[1] = 0;
		*array = u.val64;
		array++;
	}

	if (type & PERF_SAMPLE_PERIOD) {
		*array = sample->period;
		array++;
	}

	if (type & PERF_SAMPLE_READ) {
		if (read_format & PERF_FORMAT_GROUP)
			*array = sample->read.group.nr;
		else
			*array = sample->read.one.value;
		array++;

		if (read_format & PERF_FORMAT_TOTAL_TIME_ENABLED) {
			*array = sample->read.time_enabled;
			array++;
		}

		if (read_format & PERF_FORMAT_TOTAL_TIME_RUNNING) {
			*array = sample->read.time_running;
			array++;
		}

		/* PERF_FORMAT_ID is forced for PERF_SAMPLE_READ */
		if (read_format & PERF_FORMAT_GROUP) {
			sz = sample->read.group.nr *
			     sizeof(struct sample_read_value);
			memcpy(array, sample->read.group.values, sz);
			array = (void *)array + sz;
		} else {
			*array = sample->read.one.id;
			array++;
		}
	}

	if (type & PERF_SAMPLE_CALLCHAIN) {
		sz = (sample->callchain->nr + 1) * sizeof(u64);
		memcpy(array, sample->callchain, sz);
		array = (void *)array + sz;
	}

	if (type & PERF_SAMPLE_RAW) {
		u.val32[0] = sample->raw_size;
		*array = u.val64;
		array = (void *)array + sizeof(u32);

		memcpy(array, sample->raw_data, sample->raw_size);
		array = (void *)array + sample->raw_size;
	}

	if (type & PERF_SAMPLE_BRANCH_STACK) {
		sz = sample->branch_stack->nr * sizeof(struct branch_entry);
		sz += sizeof(u64);
		memcpy(array, sample->branch_stack, sz);
		array = (void *)array + sz;
	}

	if (type & PERF_SAMPLE_REGS_USER) {
		if (sample->user_regs.abi) {
			*array++ = sample->user_regs.abi;
			sz = hweight_long(sample->user_regs.mask) * sizeof(u64);
			memcpy(array, sample->user_regs.regs, sz);
			array = (void *)array + sz;
		} else {
			*array++ = 0;
		}
	}

	if (type & PERF_SAMPLE_STACK_USER) {
		sz = sample->user_stack.size;
		*array++ = sz;
		if (sz) {
			memcpy(array, sample->user_stack.data, sz);
			array = (void *)array + sz;
			*array++ = sz;
		}
	}

	if (type & PERF_SAMPLE_WEIGHT) {
		*array = sample->weight;
		array++;
	}

	if (type & PERF_SAMPLE_DATA_SRC) {
		*array = sample->data_src;
		array++;
	}

	if (type & PERF_SAMPLE_TRANSACTION) {
		*array = sample->transaction;
		array++;
	}

	if (type & PERF_SAMPLE_REGS_INTR) {
		if (sample->intr_regs.abi) {
			*array++ = sample->intr_regs.abi;
			sz = hweight_long(sample->intr_regs.mask) * sizeof(u64);
			memcpy(array, sample->intr_regs.regs, sz);
			array = (void *)array + sz;
		} else {
			*array++ = 0;
		}
	}

	if (type & PERF_SAMPLE_PHYS_ADDR) {
		*array = sample->phys_addr;
		array++;
	}

	return 0;
}