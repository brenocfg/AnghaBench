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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_un {int dummy; } ;
struct llc_conn_state_ev {scalar_t__ type; int /*<<< orphan*/  ind_prim; int /*<<< orphan*/  reason; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LLC_2_PDU_CMD_DISC ; 
 scalar_t__ LLC_2_PDU_RSP_DM ; 
 scalar_t__ LLC_CONN_EV_TYPE_ACK_TMR ; 
 scalar_t__ LLC_CONN_EV_TYPE_PDU ; 
 int /*<<< orphan*/  LLC_DISC_PRIM ; 
 int /*<<< orphan*/  LLC_DISC_REASON_ACK_TMR_EXP ; 
 int /*<<< orphan*/  LLC_DISC_REASON_RX_DISC_CMD_PDU ; 
 int /*<<< orphan*/  LLC_DISC_REASON_RX_DM_RSP_PDU ; 
 scalar_t__ LLC_PDU_IS_CMD (struct llc_pdu_un*) ; 
 scalar_t__ LLC_PDU_IS_RSP (struct llc_pdu_un*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_U (struct llc_pdu_un*) ; 
 scalar_t__ LLC_U_PDU_CMD (struct llc_pdu_un*) ; 
 scalar_t__ LLC_U_PDU_RSP (struct llc_pdu_un*) ; 
 struct llc_conn_state_ev* llc_conn_ev (struct sk_buff*) ; 
 struct llc_pdu_un* llc_pdu_un_hdr (struct sk_buff*) ; 

int llc_conn_ac_disc_ind(struct sock *sk, struct sk_buff *skb)
{
	struct llc_conn_state_ev *ev = llc_conn_ev(skb);
	u8 reason = 0;
	int rc = 0;

	if (ev->type == LLC_CONN_EV_TYPE_PDU) {
		struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

		if (LLC_PDU_IS_RSP(pdu) &&
		    LLC_PDU_TYPE_IS_U(pdu) &&
		    LLC_U_PDU_RSP(pdu) == LLC_2_PDU_RSP_DM)
			reason = LLC_DISC_REASON_RX_DM_RSP_PDU;
		else if (LLC_PDU_IS_CMD(pdu) &&
			   LLC_PDU_TYPE_IS_U(pdu) &&
			   LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_DISC)
			reason = LLC_DISC_REASON_RX_DISC_CMD_PDU;
	} else if (ev->type == LLC_CONN_EV_TYPE_ACK_TMR)
		reason = LLC_DISC_REASON_ACK_TMR_EXP;
	else
		rc = -EINVAL;
	if (!rc) {
		ev->reason   = reason;
		ev->ind_prim = LLC_DISC_PRIM;
	}
	return rc;
}