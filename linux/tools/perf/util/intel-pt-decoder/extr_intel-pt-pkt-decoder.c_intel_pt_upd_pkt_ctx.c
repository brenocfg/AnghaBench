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
struct intel_pt_pkt {int type; int /*<<< orphan*/  count; } ;
typedef  enum intel_pt_pkt_ctx { ____Placeholder_intel_pt_pkt_ctx } intel_pt_pkt_ctx ;

/* Variables and functions */
#define  INTEL_PT_BAD 159 
#define  INTEL_PT_BBP 158 
#define  INTEL_PT_BEP 157 
#define  INTEL_PT_BEP_IP 156 
#define  INTEL_PT_BIP 155 
 int INTEL_PT_BLK_4_CTX ; 
 int INTEL_PT_BLK_8_CTX ; 
#define  INTEL_PT_CBR 154 
#define  INTEL_PT_CYC 153 
#define  INTEL_PT_EXSTOP 152 
#define  INTEL_PT_EXSTOP_IP 151 
#define  INTEL_PT_FUP 150 
#define  INTEL_PT_MNT 149 
#define  INTEL_PT_MODE_EXEC 148 
#define  INTEL_PT_MODE_TSX 147 
#define  INTEL_PT_MTC 146 
#define  INTEL_PT_MWAIT 145 
 int INTEL_PT_NO_CTX ; 
#define  INTEL_PT_OVF 144 
#define  INTEL_PT_PAD 143 
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

void intel_pt_upd_pkt_ctx(const struct intel_pt_pkt *packet,
			  enum intel_pt_pkt_ctx *ctx)
{
	switch (packet->type) {
	case INTEL_PT_BAD:
	case INTEL_PT_PAD:
	case INTEL_PT_TSC:
	case INTEL_PT_TMA:
	case INTEL_PT_MTC:
	case INTEL_PT_FUP:
	case INTEL_PT_CYC:
	case INTEL_PT_CBR:
	case INTEL_PT_MNT:
	case INTEL_PT_EXSTOP:
	case INTEL_PT_EXSTOP_IP:
	case INTEL_PT_PWRE:
	case INTEL_PT_PWRX:
	case INTEL_PT_BIP:
		break;
	case INTEL_PT_TNT:
	case INTEL_PT_TIP:
	case INTEL_PT_TIP_PGD:
	case INTEL_PT_TIP_PGE:
	case INTEL_PT_MODE_EXEC:
	case INTEL_PT_MODE_TSX:
	case INTEL_PT_PIP:
	case INTEL_PT_OVF:
	case INTEL_PT_VMCS:
	case INTEL_PT_TRACESTOP:
	case INTEL_PT_PSB:
	case INTEL_PT_PSBEND:
	case INTEL_PT_PTWRITE:
	case INTEL_PT_PTWRITE_IP:
	case INTEL_PT_MWAIT:
	case INTEL_PT_BEP:
	case INTEL_PT_BEP_IP:
		*ctx = INTEL_PT_NO_CTX;
		break;
	case INTEL_PT_BBP:
		if (packet->count)
			*ctx = INTEL_PT_BLK_4_CTX;
		else
			*ctx = INTEL_PT_BLK_8_CTX;
		break;
	default:
		break;
	}
}