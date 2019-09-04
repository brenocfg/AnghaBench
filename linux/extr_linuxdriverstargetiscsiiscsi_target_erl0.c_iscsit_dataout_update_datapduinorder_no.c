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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_pdu {int status; int /*<<< orphan*/  data_sn; } ;
struct iscsi_cmd {struct iscsi_pdu* pdu_ptr; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_NORMAL ; 
#define  ISCSI_PDU_CRC_FAILED 130 
#define  ISCSI_PDU_NOT_RECEIVED 129 
 void* ISCSI_PDU_RECEIVED_OK ; 
#define  ISCSI_PDU_TIMED_OUT 128 
 int iscsit_dataout_datapduinorder_no_fbit (struct iscsi_cmd*,struct iscsi_pdu*) ; 

__attribute__((used)) static int iscsit_dataout_update_datapduinorder_no(
	struct iscsi_cmd *cmd,
	u32 data_sn,
	int f_bit)
{
	int ret = 0;
	struct iscsi_pdu *pdu = cmd->pdu_ptr;

	pdu->data_sn = data_sn;

	switch (pdu->status) {
	case ISCSI_PDU_NOT_RECEIVED:
		pdu->status = ISCSI_PDU_RECEIVED_OK;
		break;
	case ISCSI_PDU_CRC_FAILED:
		pdu->status = ISCSI_PDU_RECEIVED_OK;
		break;
	case ISCSI_PDU_TIMED_OUT:
		pdu->status = ISCSI_PDU_RECEIVED_OK;
		break;
	default:
		return DATAOUT_CANNOT_RECOVER;
	}

	if (f_bit) {
		ret = iscsit_dataout_datapduinorder_no_fbit(cmd, pdu);
		if (ret == DATAOUT_CANNOT_RECOVER)
			return ret;
	}

	return DATAOUT_NORMAL;
}