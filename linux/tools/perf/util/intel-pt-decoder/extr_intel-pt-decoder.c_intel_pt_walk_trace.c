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
struct TYPE_3__ {int type; int payload; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int ptw_payload; int pwrx_payload; int /*<<< orphan*/  to_ip; int /*<<< orphan*/  from_ip; int /*<<< orphan*/  type; } ;
struct intel_pt_decoder {int pge; int set_fup_mwait; int continuous_period; int have_tma; int have_last_ip; int cr3; int mtc_insn; int exec_mode; int fup_ptw_payload; int set_fup_ptw; int fup_mwait_payload; int fup_pwre_payload; int set_fup_pwre; int set_fup_exstop; int set_fup_bep; int /*<<< orphan*/  pos; TYPE_1__ packet; TYPE_2__ state; int /*<<< orphan*/  ip; int /*<<< orphan*/  cbr_seen; int /*<<< orphan*/  cbr; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  period_type; int /*<<< orphan*/  stack; int /*<<< orphan*/  last_ip; int /*<<< orphan*/  pkt_state; int /*<<< orphan*/  branch_enable; TYPE_1__ tnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT63 ; 
 int EAGAIN ; 
#define  INTEL_PT_BAD 159 
#define  INTEL_PT_BBP 158 
#define  INTEL_PT_BEP 157 
#define  INTEL_PT_BEP_IP 156 
#define  INTEL_PT_BIP 155 
 int /*<<< orphan*/  INTEL_PT_BLK_ITEMS ; 
#define  INTEL_PT_CBR 154 
#define  INTEL_PT_CYC 153 
#define  INTEL_PT_EXSTOP 152 
#define  INTEL_PT_EXSTOP_IP 151 
 int /*<<< orphan*/  INTEL_PT_EX_STOP ; 
#define  INTEL_PT_FUP 150 
 int /*<<< orphan*/  INTEL_PT_INSTRUCTION ; 
#define  INTEL_PT_MNT 149 
#define  INTEL_PT_MODE_EXEC 148 
#define  INTEL_PT_MODE_TSX 147 
#define  INTEL_PT_MTC 146 
#define  INTEL_PT_MWAIT 145 
#define  INTEL_PT_OVF 144 
#define  INTEL_PT_PAD 143 
 int /*<<< orphan*/  INTEL_PT_PERIOD_MTC ; 
#define  INTEL_PT_PIP 142 
#define  INTEL_PT_PSB 141 
#define  INTEL_PT_PSBEND 140 
 int /*<<< orphan*/  INTEL_PT_PTW ; 
#define  INTEL_PT_PTWRITE 139 
#define  INTEL_PT_PTWRITE_IP 138 
#define  INTEL_PT_PWRE 137 
#define  INTEL_PT_PWRX 136 
 int /*<<< orphan*/  INTEL_PT_PWR_ENTRY ; 
 int /*<<< orphan*/  INTEL_PT_PWR_EXIT ; 
 int /*<<< orphan*/  INTEL_PT_STATE_FUP ; 
 int /*<<< orphan*/  INTEL_PT_STATE_FUP_NO_TIP ; 
 int /*<<< orphan*/  INTEL_PT_STATE_TIP ; 
 int /*<<< orphan*/  INTEL_PT_STATE_TIP_PGD ; 
 int /*<<< orphan*/  INTEL_PT_STATE_TNT ; 
#define  INTEL_PT_TIP 135 
#define  INTEL_PT_TIP_PGD 134 
#define  INTEL_PT_TIP_PGE 133 
#define  INTEL_PT_TMA 132 
#define  INTEL_PT_TNT 131 
#define  INTEL_PT_TRACESTOP 130 
 int /*<<< orphan*/  INTEL_PT_TRACE_BEGIN ; 
#define  INTEL_PT_TSC 129 
#define  INTEL_PT_VMCS 128 
 int /*<<< orphan*/  intel_pt_bbp (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_bip (struct intel_pt_decoder*) ; 
 int intel_pt_bug (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_cbr (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_cyc_timestamp (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_mtc_timestamp (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_tma (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_tsc_timestamp (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_clear_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_pt_clear_tx_flags (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_fup_event (struct intel_pt_decoder*) ; 
 int intel_pt_get_next_packet (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_log_at (char*,int /*<<< orphan*/ ) ; 
 int intel_pt_mode_tsx (struct intel_pt_decoder*,int*) ; 
 int /*<<< orphan*/  intel_pt_mtc_cyc_cnt_pge (struct intel_pt_decoder*) ; 
 int intel_pt_overflow (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_set_ip (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_set_last_ip (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_update_in_tx (struct intel_pt_decoder*) ; 
 int intel_pt_walk_fup (struct intel_pt_decoder*) ; 
 int intel_pt_walk_fup_tip (struct intel_pt_decoder*) ; 
 int intel_pt_walk_psbend (struct intel_pt_decoder*) ; 
 int intel_pt_walk_tip (struct intel_pt_decoder*) ; 
 int intel_pt_walk_tnt (struct intel_pt_decoder*) ; 

__attribute__((used)) static int intel_pt_walk_trace(struct intel_pt_decoder *decoder)
{
	bool no_tip = false;
	int err;

	while (1) {
		err = intel_pt_get_next_packet(decoder);
		if (err)
			return err;
next:
		switch (decoder->packet.type) {
		case INTEL_PT_TNT:
			if (!decoder->packet.count)
				break;
			decoder->tnt = decoder->packet;
			decoder->pkt_state = INTEL_PT_STATE_TNT;
			err = intel_pt_walk_tnt(decoder);
			if (err == -EAGAIN)
				break;
			return err;

		case INTEL_PT_TIP_PGD:
			if (decoder->packet.count != 0)
				intel_pt_set_last_ip(decoder);
			decoder->pkt_state = INTEL_PT_STATE_TIP_PGD;
			return intel_pt_walk_tip(decoder);

		case INTEL_PT_TIP_PGE: {
			decoder->pge = true;
			intel_pt_mtc_cyc_cnt_pge(decoder);
			if (decoder->packet.count == 0) {
				intel_pt_log_at("Skipping zero TIP.PGE",
						decoder->pos);
				break;
			}
			intel_pt_set_ip(decoder);
			decoder->state.from_ip = 0;
			decoder->state.to_ip = decoder->ip;
			decoder->state.type |= INTEL_PT_TRACE_BEGIN;
			return 0;
		}

		case INTEL_PT_OVF:
			return intel_pt_overflow(decoder);

		case INTEL_PT_TIP:
			if (decoder->packet.count != 0)
				intel_pt_set_last_ip(decoder);
			decoder->pkt_state = INTEL_PT_STATE_TIP;
			return intel_pt_walk_tip(decoder);

		case INTEL_PT_FUP:
			if (decoder->packet.count == 0) {
				intel_pt_log_at("Skipping zero FUP",
						decoder->pos);
				no_tip = false;
				break;
			}
			intel_pt_set_last_ip(decoder);
			if (!decoder->branch_enable) {
				decoder->ip = decoder->last_ip;
				if (intel_pt_fup_event(decoder))
					return 0;
				no_tip = false;
				break;
			}
			if (decoder->set_fup_mwait)
				no_tip = true;
			err = intel_pt_walk_fup(decoder);
			if (err != -EAGAIN) {
				if (err)
					return err;
				if (no_tip)
					decoder->pkt_state =
						INTEL_PT_STATE_FUP_NO_TIP;
				else
					decoder->pkt_state = INTEL_PT_STATE_FUP;
				return 0;
			}
			if (no_tip) {
				no_tip = false;
				break;
			}
			return intel_pt_walk_fup_tip(decoder);

		case INTEL_PT_TRACESTOP:
			decoder->pge = false;
			decoder->continuous_period = false;
			intel_pt_clear_tx_flags(decoder);
			decoder->have_tma = false;
			break;

		case INTEL_PT_PSB:
			decoder->last_ip = 0;
			decoder->have_last_ip = true;
			intel_pt_clear_stack(&decoder->stack);
			err = intel_pt_walk_psbend(decoder);
			if (err == -EAGAIN)
				goto next;
			if (err)
				return err;
			/*
			 * PSB+ CBR will not have changed but cater for the
			 * possibility of another CBR change that gets caught up
			 * in the PSB+.
			 */
			if (decoder->cbr != decoder->cbr_seen)
				return 0;
			break;

		case INTEL_PT_PIP:
			decoder->cr3 = decoder->packet.payload & (BIT63 - 1);
			break;

		case INTEL_PT_MTC:
			intel_pt_calc_mtc_timestamp(decoder);
			if (decoder->period_type != INTEL_PT_PERIOD_MTC)
				break;
			/*
			 * Ensure that there has been an instruction since the
			 * last MTC.
			 */
			if (!decoder->mtc_insn)
				break;
			decoder->mtc_insn = false;
			/* Ensure that there is a timestamp */
			if (!decoder->timestamp)
				break;
			decoder->state.type = INTEL_PT_INSTRUCTION;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->mtc_insn = false;
			return 0;

		case INTEL_PT_TSC:
			intel_pt_calc_tsc_timestamp(decoder);
			break;

		case INTEL_PT_TMA:
			intel_pt_calc_tma(decoder);
			break;

		case INTEL_PT_CYC:
			intel_pt_calc_cyc_timestamp(decoder);
			break;

		case INTEL_PT_CBR:
			intel_pt_calc_cbr(decoder);
			if (decoder->cbr != decoder->cbr_seen)
				return 0;
			break;

		case INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			break;

		case INTEL_PT_MODE_TSX:
			/* MODE_TSX need not be followed by FUP */
			if (!decoder->pge) {
				intel_pt_update_in_tx(decoder);
				break;
			}
			err = intel_pt_mode_tsx(decoder, &no_tip);
			if (err)
				return err;
			goto next;

		case INTEL_PT_BAD: /* Does not happen */
			return intel_pt_bug(decoder);

		case INTEL_PT_PSBEND:
		case INTEL_PT_VMCS:
		case INTEL_PT_MNT:
		case INTEL_PT_PAD:
			break;

		case INTEL_PT_PTWRITE_IP:
			decoder->fup_ptw_payload = decoder->packet.payload;
			err = intel_pt_get_next_packet(decoder);
			if (err)
				return err;
			if (decoder->packet.type == INTEL_PT_FUP) {
				decoder->set_fup_ptw = true;
				no_tip = true;
			} else {
				intel_pt_log_at("ERROR: Missing FUP after PTWRITE",
						decoder->pos);
			}
			goto next;

		case INTEL_PT_PTWRITE:
			decoder->state.type = INTEL_PT_PTW;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->state.ptw_payload = decoder->packet.payload;
			return 0;

		case INTEL_PT_MWAIT:
			decoder->fup_mwait_payload = decoder->packet.payload;
			decoder->set_fup_mwait = true;
			break;

		case INTEL_PT_PWRE:
			if (decoder->set_fup_mwait) {
				decoder->fup_pwre_payload =
							decoder->packet.payload;
				decoder->set_fup_pwre = true;
				break;
			}
			decoder->state.type = INTEL_PT_PWR_ENTRY;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->state.pwrx_payload = decoder->packet.payload;
			return 0;

		case INTEL_PT_EXSTOP_IP:
			err = intel_pt_get_next_packet(decoder);
			if (err)
				return err;
			if (decoder->packet.type == INTEL_PT_FUP) {
				decoder->set_fup_exstop = true;
				no_tip = true;
			} else {
				intel_pt_log_at("ERROR: Missing FUP after EXSTOP",
						decoder->pos);
			}
			goto next;

		case INTEL_PT_EXSTOP:
			decoder->state.type = INTEL_PT_EX_STOP;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			return 0;

		case INTEL_PT_PWRX:
			decoder->state.type = INTEL_PT_PWR_EXIT;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->state.pwrx_payload = decoder->packet.payload;
			return 0;

		case INTEL_PT_BBP:
			intel_pt_bbp(decoder);
			break;

		case INTEL_PT_BIP:
			intel_pt_bip(decoder);
			break;

		case INTEL_PT_BEP:
			decoder->state.type = INTEL_PT_BLK_ITEMS;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			return 0;

		case INTEL_PT_BEP_IP:
			err = intel_pt_get_next_packet(decoder);
			if (err)
				return err;
			if (decoder->packet.type == INTEL_PT_FUP) {
				decoder->set_fup_bep = true;
				no_tip = true;
			} else {
				intel_pt_log_at("ERROR: Missing FUP after BEP",
						decoder->pos);
			}
			goto next;

		default:
			return intel_pt_bug(decoder);
		}
	}
}