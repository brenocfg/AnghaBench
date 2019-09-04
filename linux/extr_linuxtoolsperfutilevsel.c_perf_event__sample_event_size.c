#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sample_read_value {int dummy; } ;
struct sample_event {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  mask; scalar_t__ abi; } ;
struct TYPE_13__ {size_t size; } ;
struct TYPE_12__ {int /*<<< orphan*/  mask; scalar_t__ abi; } ;
struct TYPE_8__ {int nr; } ;
struct TYPE_9__ {TYPE_1__ group; } ;
struct perf_sample {TYPE_7__ intr_regs; TYPE_6__ user_stack; TYPE_5__ user_regs; TYPE_4__* branch_stack; scalar_t__ raw_size; TYPE_3__* callchain; TYPE_2__ read; } ;
struct branch_entry {int dummy; } ;
struct TYPE_11__ {int nr; } ;
struct TYPE_10__ {int nr; } ;

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

size_t perf_event__sample_event_size(const struct perf_sample *sample, u64 type,
				     u64 read_format)
{
	size_t sz, result = sizeof(struct sample_event);

	if (type & PERF_SAMPLE_IDENTIFIER)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_IP)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_TID)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_TIME)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_ADDR)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_ID)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_STREAM_ID)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_CPU)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_PERIOD)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_READ) {
		result += sizeof(u64);
		if (read_format & PERF_FORMAT_TOTAL_TIME_ENABLED)
			result += sizeof(u64);
		if (read_format & PERF_FORMAT_TOTAL_TIME_RUNNING)
			result += sizeof(u64);
		/* PERF_FORMAT_ID is forced for PERF_SAMPLE_READ */
		if (read_format & PERF_FORMAT_GROUP) {
			sz = sample->read.group.nr *
			     sizeof(struct sample_read_value);
			result += sz;
		} else {
			result += sizeof(u64);
		}
	}

	if (type & PERF_SAMPLE_CALLCHAIN) {
		sz = (sample->callchain->nr + 1) * sizeof(u64);
		result += sz;
	}

	if (type & PERF_SAMPLE_RAW) {
		result += sizeof(u32);
		result += sample->raw_size;
	}

	if (type & PERF_SAMPLE_BRANCH_STACK) {
		sz = sample->branch_stack->nr * sizeof(struct branch_entry);
		sz += sizeof(u64);
		result += sz;
	}

	if (type & PERF_SAMPLE_REGS_USER) {
		if (sample->user_regs.abi) {
			result += sizeof(u64);
			sz = hweight_long(sample->user_regs.mask) * sizeof(u64);
			result += sz;
		} else {
			result += sizeof(u64);
		}
	}

	if (type & PERF_SAMPLE_STACK_USER) {
		sz = sample->user_stack.size;
		result += sizeof(u64);
		if (sz) {
			result += sz;
			result += sizeof(u64);
		}
	}

	if (type & PERF_SAMPLE_WEIGHT)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_DATA_SRC)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_TRANSACTION)
		result += sizeof(u64);

	if (type & PERF_SAMPLE_REGS_INTR) {
		if (sample->intr_regs.abi) {
			result += sizeof(u64);
			sz = hweight_long(sample->intr_regs.mask) * sizeof(u64);
			result += sz;
		} else {
			result += sizeof(u64);
		}
	}

	if (type & PERF_SAMPLE_PHYS_ADDR)
		result += sizeof(u64);

	return result;
}