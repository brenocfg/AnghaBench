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
struct llc_pdu_sn {int ctrl_2; int ctrl_1; } ;

/* Variables and functions */
#define  LLC_PDU_TYPE_I 130 
#define  LLC_PDU_TYPE_S 129 
#define  LLC_PDU_TYPE_U 128 
 int /*<<< orphan*/  llc_pdu_decode_pdu_type (struct sk_buff*,int*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 

void llc_pdu_set_pf_bit(struct sk_buff *skb, u8 bit_value)
{
	u8 pdu_type;
	struct llc_pdu_sn *pdu;

	llc_pdu_decode_pdu_type(skb, &pdu_type);
	pdu = llc_pdu_sn_hdr(skb);

	switch (pdu_type) {
	case LLC_PDU_TYPE_I:
	case LLC_PDU_TYPE_S:
		pdu->ctrl_2 = (pdu->ctrl_2 & 0xFE) | bit_value;
		break;
	case LLC_PDU_TYPE_U:
		pdu->ctrl_1 |= (pdu->ctrl_1 & 0xEF) | (bit_value << 4);
		break;
	}
}