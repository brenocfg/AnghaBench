#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct intel_pt_decoder {int period_type; int timestamp; int timestamp_insn_cnt; int period_mask; int last_masked_timestamp; TYPE_1__ state; int /*<<< orphan*/  period_insn_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_INSTRUCTION ; 
#define  INTEL_PT_PERIOD_INSTRUCTIONS 131 
#define  INTEL_PT_PERIOD_MTC 130 
#define  INTEL_PT_PERIOD_NONE 129 
#define  INTEL_PT_PERIOD_TICKS 128 

__attribute__((used)) static void intel_pt_sample_insn(struct intel_pt_decoder *decoder)
{
	uint64_t timestamp, masked_timestamp;

	switch (decoder->period_type) {
	case INTEL_PT_PERIOD_INSTRUCTIONS:
		decoder->period_insn_cnt = 0;
		break;
	case INTEL_PT_PERIOD_TICKS:
		timestamp = decoder->timestamp + decoder->timestamp_insn_cnt;
		masked_timestamp = timestamp & decoder->period_mask;
		decoder->last_masked_timestamp = masked_timestamp;
		break;
	case INTEL_PT_PERIOD_NONE:
	case INTEL_PT_PERIOD_MTC:
	default:
		break;
	}

	decoder->state.type |= INTEL_PT_INSTRUCTION;
}