#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_pt_insn {scalar_t__ op; scalar_t__ branch; scalar_t__ length; scalar_t__ rel; } ;
struct TYPE_6__ {int payload; scalar_t__ count; } ;
struct TYPE_5__ {int type; scalar_t__ to_ip; scalar_t__ from_ip; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ count; } ;
struct intel_pt_decoder {int sample_cyc; TYPE_3__ tnt; scalar_t__ ip; TYPE_2__ state; void* pkt_state; scalar_t__ last_ip; scalar_t__ pkt_step; TYPE_1__ packet; scalar_t__ ret_addr; int /*<<< orphan*/  return_compression; } ;

/* Variables and functions */
 int BIT63 ; 
 int EAGAIN ; 
 int ENOENT ; 
 scalar_t__ INTEL_PT_BR_CONDITIONAL ; 
 scalar_t__ INTEL_PT_BR_INDIRECT ; 
 int INTEL_PT_INSTRUCTION ; 
 scalar_t__ INTEL_PT_OP_RET ; 
 int INTEL_PT_RETURN ; 
 void* INTEL_PT_STATE_ERR3 ; 
 void* INTEL_PT_STATE_IN_SYNC ; 
 void* INTEL_PT_STATE_TNT_CONT ; 
 scalar_t__ INTEL_PT_TIP ; 
 int intel_pt_bug (struct intel_pt_decoder*) ; 
 int intel_pt_get_next_packet (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_log_at (char*,scalar_t__) ; 
 int /*<<< orphan*/  intel_pt_set_last_ip (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_update_sample_time (struct intel_pt_decoder*) ; 
 int intel_pt_walk_insn (struct intel_pt_decoder*,struct intel_pt_insn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_walk_tnt(struct intel_pt_decoder *decoder)
{
	struct intel_pt_insn intel_pt_insn;
	int err;

	while (1) {
		err = intel_pt_walk_insn(decoder, &intel_pt_insn, 0);
		if (err == INTEL_PT_RETURN)
			return 0;
		if (err)
			return err;

		if (intel_pt_insn.op == INTEL_PT_OP_RET) {
			if (!decoder->return_compression) {
				intel_pt_log_at("ERROR: RET when expecting conditional branch",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				return -ENOENT;
			}
			if (!decoder->ret_addr) {
				intel_pt_log_at("ERROR: Bad RET compression (stack empty)",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				return -ENOENT;
			}
			if (!(decoder->tnt.payload & BIT63)) {
				intel_pt_log_at("ERROR: Bad RET compression (TNT=N)",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				return -ENOENT;
			}
			decoder->tnt.count -= 1;
			if (decoder->tnt.count)
				decoder->pkt_state = INTEL_PT_STATE_TNT_CONT;
			else
				decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->tnt.payload <<= 1;
			decoder->state.from_ip = decoder->ip;
			decoder->ip = decoder->ret_addr;
			decoder->state.to_ip = decoder->ip;
			return 0;
		}

		if (intel_pt_insn.branch == INTEL_PT_BR_INDIRECT) {
			/* Handle deferred TIPs */
			err = intel_pt_get_next_packet(decoder);
			if (err)
				return err;
			if (decoder->packet.type != INTEL_PT_TIP ||
			    decoder->packet.count == 0) {
				intel_pt_log_at("ERROR: Missing deferred TIP for indirect branch",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				decoder->pkt_step = 0;
				return -ENOENT;
			}
			intel_pt_set_last_ip(decoder);
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = decoder->last_ip;
			decoder->ip = decoder->last_ip;
			return 0;
		}

		if (intel_pt_insn.branch == INTEL_PT_BR_CONDITIONAL) {
			decoder->tnt.count -= 1;
			if (decoder->tnt.count)
				decoder->pkt_state = INTEL_PT_STATE_TNT_CONT;
			else
				decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			if (decoder->tnt.payload & BIT63) {
				decoder->tnt.payload <<= 1;
				decoder->state.from_ip = decoder->ip;
				decoder->ip += intel_pt_insn.length +
					       intel_pt_insn.rel;
				decoder->state.to_ip = decoder->ip;
				return 0;
			}
			/* Instruction sample for a non-taken branch */
			if (decoder->state.type & INTEL_PT_INSTRUCTION) {
				decoder->tnt.payload <<= 1;
				decoder->state.type = INTEL_PT_INSTRUCTION;
				decoder->state.from_ip = decoder->ip;
				decoder->state.to_ip = 0;
				decoder->ip += intel_pt_insn.length;
				return 0;
			}
			decoder->sample_cyc = false;
			decoder->ip += intel_pt_insn.length;
			if (!decoder->tnt.count) {
				intel_pt_update_sample_time(decoder);
				return -EAGAIN;
			}
			decoder->tnt.payload <<= 1;
			continue;
		}

		return intel_pt_bug(decoder);
	}
}