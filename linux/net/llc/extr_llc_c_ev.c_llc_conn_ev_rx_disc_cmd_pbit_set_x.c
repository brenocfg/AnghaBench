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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_un {int dummy; } ;

/* Variables and functions */
 scalar_t__ LLC_2_PDU_CMD_DISC ; 
 scalar_t__ LLC_PDU_IS_CMD (struct llc_pdu_un const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_U (struct llc_pdu_un const*) ; 
 scalar_t__ LLC_U_PDU_CMD (struct llc_pdu_un const*) ; 
 struct llc_pdu_un* llc_pdu_un_hdr (struct sk_buff*) ; 

int llc_conn_ev_rx_disc_cmd_pbit_set_x(struct sock *sk, struct sk_buff *skb)
{
	const struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return LLC_PDU_IS_CMD(pdu) && LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_2_PDU_CMD_DISC ? 0 : 1;
}