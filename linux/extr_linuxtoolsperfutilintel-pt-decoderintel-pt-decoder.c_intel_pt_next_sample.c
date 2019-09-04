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
typedef  scalar_t__ uint64_t ;
struct intel_pt_decoder {int period_type; scalar_t__ period_insn_cnt; scalar_t__ period; } ;

/* Variables and functions */
#define  INTEL_PT_PERIOD_INSTRUCTIONS 131 
#define  INTEL_PT_PERIOD_MTC 130 
#define  INTEL_PT_PERIOD_NONE 129 
#define  INTEL_PT_PERIOD_TICKS 128 
 scalar_t__ intel_pt_next_period (struct intel_pt_decoder*) ; 

__attribute__((used)) static uint64_t intel_pt_next_sample(struct intel_pt_decoder *decoder)
{
	switch (decoder->period_type) {
	case INTEL_PT_PERIOD_INSTRUCTIONS:
		return decoder->period - decoder->period_insn_cnt;
	case INTEL_PT_PERIOD_TICKS:
		return intel_pt_next_period(decoder);
	case INTEL_PT_PERIOD_NONE:
	case INTEL_PT_PERIOD_MTC:
	default:
		return 0;
	}
}