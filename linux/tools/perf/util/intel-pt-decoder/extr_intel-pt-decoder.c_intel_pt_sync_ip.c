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
struct TYPE_2__ {int /*<<< orphan*/  to_ip; scalar_t__ from_ip; scalar_t__ type; } ;
struct intel_pt_decoder {int set_fup_tx_flags; int set_fup_ptw; int set_fup_mwait; int set_fup_pwre; int set_fup_exstop; int set_fup_bep; int overflow; int /*<<< orphan*/  ip; TYPE_1__ state; void* pkt_state; int /*<<< orphan*/  branch_enable; } ;

/* Variables and functions */
 void* INTEL_PT_STATE_IN_SYNC ; 
 int /*<<< orphan*/  intel_pt_log (char*) ; 
 int /*<<< orphan*/  intel_pt_log_to (char*,int /*<<< orphan*/ ) ; 
 int intel_pt_walk_to_ip (struct intel_pt_decoder*) ; 

__attribute__((used)) static int intel_pt_sync_ip(struct intel_pt_decoder *decoder)
{
	int err;

	decoder->set_fup_tx_flags = false;
	decoder->set_fup_ptw = false;
	decoder->set_fup_mwait = false;
	decoder->set_fup_pwre = false;
	decoder->set_fup_exstop = false;
	decoder->set_fup_bep = false;

	if (!decoder->branch_enable) {
		decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
		decoder->overflow = false;
		decoder->state.type = 0; /* Do not have a sample */
		return 0;
	}

	intel_pt_log("Scanning for full IP\n");
	err = intel_pt_walk_to_ip(decoder);
	if (err)
		return err;

	decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
	decoder->overflow = false;

	decoder->state.from_ip = 0;
	decoder->state.to_ip = decoder->ip;
	intel_pt_log_to("Setting IP", decoder->ip);

	return 0;
}