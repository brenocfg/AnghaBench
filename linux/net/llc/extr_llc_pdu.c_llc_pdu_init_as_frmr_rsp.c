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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct llc_pdu_sn {int ctrl_1; int /*<<< orphan*/  ctrl_2; } ;
struct llc_frmr_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRMR_INFO_SET_C_R_BIT (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_INVALID_PDU_CTRL_IND (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_INVALID_PDU_INFO_IND (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_PDU_INFO_2LONG_IND (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_PDU_INVALID_Nr_IND (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_PDU_INVALID_Ns_IND (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_REJ_CNTRL (struct llc_frmr_info*,int*) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_Vr (struct llc_frmr_info*,int) ; 
 int /*<<< orphan*/  FRMR_INFO_SET_Vs (struct llc_frmr_info*,int) ; 
 int LLC_2_PDU_RSP_FRMR ; 
 int LLC_PDU_TYPE_U ; 
 int LLC_U_PF_BIT_MASK ; 
 int llc_pdu_get_pf_bit (struct llc_pdu_sn*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

void llc_pdu_init_as_frmr_rsp(struct sk_buff *skb, struct llc_pdu_sn *prev_pdu,
			      u8 f_bit, u8 vs, u8 vr, u8 vzyxw)
{
	struct llc_frmr_info *frmr_info;
	u8 prev_pf = 0;
	u8 *ctrl;
	struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_FRMR;
	pdu->ctrl_1 |= ((f_bit & 1) << 4) & LLC_U_PF_BIT_MASK;

	frmr_info = (struct llc_frmr_info *)&pdu->ctrl_2;
	ctrl = (u8 *)&prev_pdu->ctrl_1;
	FRMR_INFO_SET_REJ_CNTRL(frmr_info,ctrl);
	FRMR_INFO_SET_Vs(frmr_info, vs);
	FRMR_INFO_SET_Vr(frmr_info, vr);
	prev_pf = llc_pdu_get_pf_bit(prev_pdu);
	FRMR_INFO_SET_C_R_BIT(frmr_info, prev_pf);
	FRMR_INFO_SET_INVALID_PDU_CTRL_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_INVALID_PDU_INFO_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_PDU_INFO_2LONG_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_PDU_INVALID_Nr_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_PDU_INVALID_Ns_IND(frmr_info, vzyxw);
	skb_put(skb, sizeof(struct llc_frmr_info));
}