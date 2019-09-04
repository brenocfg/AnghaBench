#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct intel_pt_insn {scalar_t__ branch; scalar_t__ rel; scalar_t__ length; } ;
struct TYPE_4__ {int type; scalar_t__ to_ip; scalar_t__ from_ip; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct intel_pt_decoder {scalar_t__ pkt_state; int pge; int continuous_period; scalar_t__ ip; TYPE_2__ state; int /*<<< orphan*/  data; scalar_t__ (* pgd_ip ) (scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ last_ip; TYPE_1__ packet; scalar_t__ no_progress; } ;

/* Variables and functions */
 int ENOENT ; 
 int INTEL_PT_BRANCH ; 
 scalar_t__ INTEL_PT_BR_CONDITIONAL ; 
 scalar_t__ INTEL_PT_BR_INDIRECT ; 
 int INTEL_PT_RETURN ; 
 scalar_t__ INTEL_PT_STATE_ERR_RESYNC ; 
 void* INTEL_PT_STATE_IN_SYNC ; 
 scalar_t__ INTEL_PT_STATE_TIP_PGD ; 
 int intel_pt_bug (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_log_at (char*,scalar_t__) ; 
 int intel_pt_walk_insn (struct intel_pt_decoder*,struct intel_pt_insn*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_walk_tip(struct intel_pt_decoder *decoder)
{
	struct intel_pt_insn intel_pt_insn;
	int err;

	err = intel_pt_walk_insn(decoder, &intel_pt_insn, 0);
	if (err == INTEL_PT_RETURN &&
	    decoder->pgd_ip &&
	    decoder->pkt_state == INTEL_PT_STATE_TIP_PGD &&
	    (decoder->state.type & INTEL_PT_BRANCH) &&
	    decoder->pgd_ip(decoder->state.to_ip, decoder->data)) {
		/* Unconditional branch leaving filter region */
		decoder->no_progress = 0;
		decoder->pge = false;
		decoder->continuous_period = false;
		decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
		decoder->state.to_ip = 0;
		return 0;
	}
	if (err == INTEL_PT_RETURN)
		return 0;
	if (err)
		return err;

	if (intel_pt_insn.branch == INTEL_PT_BR_INDIRECT) {
		if (decoder->pkt_state == INTEL_PT_STATE_TIP_PGD) {
			decoder->pge = false;
			decoder->continuous_period = false;
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			if (decoder->packet.count != 0)
				decoder->ip = decoder->last_ip;
		} else {
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->state.from_ip = decoder->ip;
			if (decoder->packet.count == 0) {
				decoder->state.to_ip = 0;
			} else {
				decoder->state.to_ip = decoder->last_ip;
				decoder->ip = decoder->last_ip;
			}
		}
		return 0;
	}

	if (intel_pt_insn.branch == INTEL_PT_BR_CONDITIONAL) {
		uint64_t to_ip = decoder->ip + intel_pt_insn.length +
				 intel_pt_insn.rel;

		if (decoder->pgd_ip &&
		    decoder->pkt_state == INTEL_PT_STATE_TIP_PGD &&
		    decoder->pgd_ip(to_ip, decoder->data)) {
			/* Conditional branch leaving filter region */
			decoder->pge = false;
			decoder->continuous_period = false;
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->ip = to_ip;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			return 0;
		}
		intel_pt_log_at("ERROR: Conditional branch when expecting indirect branch",
				decoder->ip);
		decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
		return -ENOENT;
	}

	return intel_pt_bug(decoder);
}