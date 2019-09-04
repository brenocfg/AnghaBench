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
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_pdu_un {int dummy; } ;

/* Variables and functions */
#define  LLC_2_PDU_CMD_DISC 129 
#define  LLC_2_PDU_CMD_SABME 128 
 scalar_t__ LLC_PDU_IS_CMD (struct llc_pdu_un const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_I (struct llc_pdu_un const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_S (struct llc_pdu_un const*) ; 
 scalar_t__ LLC_PDU_TYPE_IS_U (struct llc_pdu_un const*) ; 
 int LLC_U_PDU_CMD (struct llc_pdu_un const*) ; 
 struct llc_pdu_un* llc_pdu_un_hdr (struct sk_buff*) ; 

int llc_conn_ev_rx_xxx_cmd_pbit_set_x(struct sock *sk, struct sk_buff *skb)
{
	u16 rc = 1;
	const struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	if (LLC_PDU_IS_CMD(pdu)) {
		if (LLC_PDU_TYPE_IS_I(pdu) || LLC_PDU_TYPE_IS_S(pdu))
			rc = 0;
		else if (LLC_PDU_TYPE_IS_U(pdu))
			switch (LLC_U_PDU_CMD(pdu)) {
			case LLC_2_PDU_CMD_SABME:
			case LLC_2_PDU_CMD_DISC:
				rc = 0;
				break;
			}
	}
	return rc;
}