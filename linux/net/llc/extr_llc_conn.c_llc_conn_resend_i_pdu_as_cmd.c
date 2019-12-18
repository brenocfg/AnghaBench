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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct llc_sock {int vS; int /*<<< orphan*/  pdu_unack_q; } ;
struct llc_pdu_sn {int dummy; } ;

/* Variables and functions */
 int LLC_2_SEQ_NBR_MODULO ; 
 int LLC_I_GET_NS (struct llc_pdu_sn*) ; 
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  llc_conn_remove_acked_pdus (struct sock*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_conn_send_pdus (struct sock*) ; 
 int /*<<< orphan*/  llc_pdu_set_cmd_rsp (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_set_pf_bit (struct sk_buff*,scalar_t__) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void llc_conn_resend_i_pdu_as_cmd(struct sock *sk, u8 nr, u8 first_p_bit)
{
	struct sk_buff *skb;
	struct llc_pdu_sn *pdu;
	u16 nbr_unack_pdus;
	struct llc_sock *llc;
	u8 howmany_resend = 0;

	llc_conn_remove_acked_pdus(sk, nr, &nbr_unack_pdus);
	if (!nbr_unack_pdus)
		goto out;
	/*
	 * Process unack PDUs only if unack queue is not empty; remove
	 * appropriate PDUs, fix them up, and put them on mac_pdu_q.
	 */
	llc = llc_sk(sk);

	while ((skb = skb_dequeue(&llc->pdu_unack_q)) != NULL) {
		pdu = llc_pdu_sn_hdr(skb);
		llc_pdu_set_cmd_rsp(skb, LLC_PDU_CMD);
		llc_pdu_set_pf_bit(skb, first_p_bit);
		skb_queue_tail(&sk->sk_write_queue, skb);
		first_p_bit = 0;
		llc->vS = LLC_I_GET_NS(pdu);
		howmany_resend++;
	}
	if (howmany_resend > 0)
		llc->vS = (llc->vS + 1) % LLC_2_SEQ_NBR_MODULO;
	/* any PDUs to re-send are queued up; start sending to MAC */
	llc_conn_send_pdus(sk);
out:;
}