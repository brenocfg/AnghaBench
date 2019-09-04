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
struct llc_pdu_sn {int ctrl_1; int ctrl_2; } ;

/* Variables and functions */
#define  LLC_PDU_TYPE_I 130 
#define  LLC_PDU_TYPE_S 129 
#define  LLC_PDU_TYPE_U 128 
 int LLC_S_PF_BIT_MASK ; 
 int LLC_U_PF_BIT_MASK ; 

__attribute__((used)) static u8 llc_pdu_get_pf_bit(struct llc_pdu_sn *pdu)
{
	u8 pdu_type;
	u8 pf_bit = 0;

	if (pdu->ctrl_1 & 1) {
		if ((pdu->ctrl_1 & LLC_PDU_TYPE_U) == LLC_PDU_TYPE_U)
			pdu_type = LLC_PDU_TYPE_U;
		else
			pdu_type = LLC_PDU_TYPE_S;
	} else
		pdu_type = LLC_PDU_TYPE_I;
	switch (pdu_type) {
	case LLC_PDU_TYPE_I:
	case LLC_PDU_TYPE_S:
		pf_bit = pdu->ctrl_2 & LLC_S_PF_BIT_MASK;
		break;
	case LLC_PDU_TYPE_U:
		pf_bit = (pdu->ctrl_1 & LLC_U_PF_BIT_MASK) >> 4;
		break;
	}
	return pf_bit;
}