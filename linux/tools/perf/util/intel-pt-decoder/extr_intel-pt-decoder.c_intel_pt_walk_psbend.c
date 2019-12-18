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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int type; int payload; int /*<<< orphan*/  count; } ;
struct intel_pt_decoder {int in_psb; int have_tma; int exec_mode; int cr3; int pge; TYPE_2__ state; int /*<<< orphan*/  period_type; TYPE_1__ packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT63 ; 
 int EAGAIN ; 
#define  INTEL_PT_BAD 159 
#define  INTEL_PT_BBP 158 
#define  INTEL_PT_BEP 157 
#define  INTEL_PT_BEP_IP 156 
#define  INTEL_PT_BIP 155 
#define  INTEL_PT_CBR 154 
#define  INTEL_PT_CYC 153 
#define  INTEL_PT_EXSTOP 152 
#define  INTEL_PT_EXSTOP_IP 151 
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
#define  INTEL_PT_PTWRITE 139 
#define  INTEL_PT_PTWRITE_IP 138 
#define  INTEL_PT_PWRE 137 
#define  INTEL_PT_PWRX 136 
#define  INTEL_PT_TIP 135 
#define  INTEL_PT_TIP_PGD 134 
#define  INTEL_PT_TIP_PGE 133 
#define  INTEL_PT_TMA 132 
#define  INTEL_PT_TNT 131 
#define  INTEL_PT_TRACESTOP 130 
#define  INTEL_PT_TSC 129 
#define  INTEL_PT_VMCS 128 
 int /*<<< orphan*/  intel_pt_calc_cbr (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_mtc_timestamp (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_tma (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_calc_tsc_timestamp (struct intel_pt_decoder*) ; 
 int intel_pt_get_next_packet (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_log (char*) ; 
 int intel_pt_overflow (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_set_last_ip (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_update_in_tx (struct intel_pt_decoder*) ; 

__attribute__((used)) static int intel_pt_walk_psbend(struct intel_pt_decoder *decoder)
{
	int err;

	decoder->in_psb = true;

	while (1) {
		err = intel_pt_get_next_packet(decoder);
		if (err)
			goto out;

		switch (decoder->packet.type) {
		case INTEL_PT_PSBEND:
			err = 0;
			goto out;

		case INTEL_PT_TIP_PGD:
		case INTEL_PT_TIP_PGE:
		case INTEL_PT_TIP:
		case INTEL_PT_TNT:
		case INTEL_PT_TRACESTOP:
		case INTEL_PT_BAD:
		case INTEL_PT_PSB:
		case INTEL_PT_PTWRITE:
		case INTEL_PT_PTWRITE_IP:
		case INTEL_PT_EXSTOP:
		case INTEL_PT_EXSTOP_IP:
		case INTEL_PT_MWAIT:
		case INTEL_PT_PWRE:
		case INTEL_PT_PWRX:
		case INTEL_PT_BBP:
		case INTEL_PT_BIP:
		case INTEL_PT_BEP:
		case INTEL_PT_BEP_IP:
			decoder->have_tma = false;
			intel_pt_log("ERROR: Unexpected packet\n");
			err = -EAGAIN;
			goto out;

		case INTEL_PT_OVF:
			err = intel_pt_overflow(decoder);
			goto out;

		case INTEL_PT_TSC:
			intel_pt_calc_tsc_timestamp(decoder);
			break;

		case INTEL_PT_TMA:
			intel_pt_calc_tma(decoder);
			break;

		case INTEL_PT_CBR:
			intel_pt_calc_cbr(decoder);
			break;

		case INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			break;

		case INTEL_PT_PIP:
			decoder->cr3 = decoder->packet.payload & (BIT63 - 1);
			break;

		case INTEL_PT_FUP:
			decoder->pge = true;
			if (decoder->packet.count)
				intel_pt_set_last_ip(decoder);
			break;

		case INTEL_PT_MODE_TSX:
			intel_pt_update_in_tx(decoder);
			break;

		case INTEL_PT_MTC:
			intel_pt_calc_mtc_timestamp(decoder);
			if (decoder->period_type == INTEL_PT_PERIOD_MTC)
				decoder->state.type |= INTEL_PT_INSTRUCTION;
			break;

		case INTEL_PT_CYC:
		case INTEL_PT_VMCS:
		case INTEL_PT_MNT:
		case INTEL_PT_PAD:
		default:
			break;
		}
	}
out:
	decoder->in_psb = false;

	return err;
}