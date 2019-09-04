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
struct TYPE_2__ {scalar_t__ type; } ;
struct intel_pt_decoder {int pge; int continuous_period; int have_last_ip; int /*<<< orphan*/  pkt_state; TYPE_1__ state; scalar_t__ ip; int /*<<< orphan*/  stack; scalar_t__ last_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_STATE_IN_SYNC ; 
 int /*<<< orphan*/  INTEL_PT_STATE_NO_IP ; 
 int /*<<< orphan*/  intel_pt_clear_stack (int /*<<< orphan*/ *) ; 
 int intel_pt_scan_for_psb (struct intel_pt_decoder*) ; 
 int intel_pt_sync_ip (struct intel_pt_decoder*) ; 
 int intel_pt_walk_psb (struct intel_pt_decoder*) ; 

__attribute__((used)) static int intel_pt_sync(struct intel_pt_decoder *decoder)
{
	int err;

	decoder->pge = false;
	decoder->continuous_period = false;
	decoder->have_last_ip = false;
	decoder->last_ip = 0;
	decoder->ip = 0;
	intel_pt_clear_stack(&decoder->stack);

	err = intel_pt_scan_for_psb(decoder);
	if (err)
		return err;

	decoder->have_last_ip = true;
	decoder->pkt_state = INTEL_PT_STATE_NO_IP;

	err = intel_pt_walk_psb(decoder);
	if (err)
		return err;

	if (decoder->ip) {
		decoder->state.type = 0; /* Do not have a sample */
		decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
	} else {
		return intel_pt_sync_ip(decoder);
	}

	return 0;
}