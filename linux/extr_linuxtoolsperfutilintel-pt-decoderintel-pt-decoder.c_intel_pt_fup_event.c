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
struct TYPE_2__ {scalar_t__ to_ip; int /*<<< orphan*/  from_ip; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  pwre_payload; int /*<<< orphan*/  mwait_payload; int /*<<< orphan*/  ptw_payload; } ;
struct intel_pt_decoder {int set_fup_tx_flags; int set_fup_ptw; int set_fup_mwait; int set_fup_pwre; int set_fup_exstop; TYPE_1__ state; int /*<<< orphan*/  ip; int /*<<< orphan*/  fup_pwre_payload; int /*<<< orphan*/  fup_mwait_payload; int /*<<< orphan*/  fup_ptw_payload; int /*<<< orphan*/  fup_tx_flags; int /*<<< orphan*/  tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_BRANCH ; 
 int /*<<< orphan*/  INTEL_PT_EX_STOP ; 
 int /*<<< orphan*/  INTEL_PT_FUP_IP ; 
 int /*<<< orphan*/  INTEL_PT_MWAIT_OP ; 
 int /*<<< orphan*/  INTEL_PT_PTW ; 
 int /*<<< orphan*/  INTEL_PT_PWR_ENTRY ; 
 int /*<<< orphan*/  INTEL_PT_TRANSACTION ; 

__attribute__((used)) static bool intel_pt_fup_event(struct intel_pt_decoder *decoder)
{
	bool ret = false;

	if (decoder->set_fup_tx_flags) {
		decoder->set_fup_tx_flags = false;
		decoder->tx_flags = decoder->fup_tx_flags;
		decoder->state.type = INTEL_PT_TRANSACTION;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.flags = decoder->fup_tx_flags;
		return true;
	}
	if (decoder->set_fup_ptw) {
		decoder->set_fup_ptw = false;
		decoder->state.type = INTEL_PT_PTW;
		decoder->state.flags |= INTEL_PT_FUP_IP;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.ptw_payload = decoder->fup_ptw_payload;
		return true;
	}
	if (decoder->set_fup_mwait) {
		decoder->set_fup_mwait = false;
		decoder->state.type = INTEL_PT_MWAIT_OP;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.mwait_payload = decoder->fup_mwait_payload;
		ret = true;
	}
	if (decoder->set_fup_pwre) {
		decoder->set_fup_pwre = false;
		decoder->state.type |= INTEL_PT_PWR_ENTRY;
		decoder->state.type &= ~INTEL_PT_BRANCH;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.pwre_payload = decoder->fup_pwre_payload;
		ret = true;
	}
	if (decoder->set_fup_exstop) {
		decoder->set_fup_exstop = false;
		decoder->state.type |= INTEL_PT_EX_STOP;
		decoder->state.type &= ~INTEL_PT_BRANCH;
		decoder->state.flags |= INTEL_PT_FUP_IP;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		ret = true;
	}
	return ret;
}