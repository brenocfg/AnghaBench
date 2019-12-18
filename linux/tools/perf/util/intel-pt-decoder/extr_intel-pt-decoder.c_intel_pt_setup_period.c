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
typedef  int uint64_t ;
struct intel_pt_decoder {scalar_t__ period_type; int period_mask; int period_ticks; int /*<<< orphan*/  period; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_PERIOD_TICKS ; 
 int intel_pt_lower_power_of_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pt_setup_period(struct intel_pt_decoder *decoder)
{
	if (decoder->period_type == INTEL_PT_PERIOD_TICKS) {
		uint64_t period;

		period = intel_pt_lower_power_of_2(decoder->period);
		decoder->period_mask  = ~(period - 1);
		decoder->period_ticks = period;
	}
}