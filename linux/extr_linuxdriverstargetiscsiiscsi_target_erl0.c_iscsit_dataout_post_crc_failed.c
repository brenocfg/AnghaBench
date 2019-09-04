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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_pdu {int status; } ;
struct iscsi_data {int /*<<< orphan*/  offset; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {TYPE_2__* sess; } ;
struct iscsi_cmd {struct iscsi_pdu* pdu_ptr; struct iscsi_conn* conn; } ;
struct TYPE_4__ {TYPE_1__* sess_ops; } ;
struct TYPE_3__ {scalar_t__ DataPDUInOrder; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
#define  ISCSI_PDU_CRC_FAILED 130 
#define  ISCSI_PDU_NOT_RECEIVED 129 
#define  ISCSI_PDU_TIMED_OUT 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int iscsit_recover_dataout_sequence (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_dataout_post_crc_failed(
	struct iscsi_cmd *cmd,
	unsigned char *buf)
{
	struct iscsi_conn *conn = cmd->conn;
	struct iscsi_pdu *pdu;
	struct iscsi_data *hdr = (struct iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	if (conn->sess->sess_ops->DataPDUInOrder)
		goto recover;
	/*
	 * The rest of this function is only called when DataPDUInOrder=No.
	 */
	pdu = cmd->pdu_ptr;

	switch (pdu->status) {
	case ISCSI_PDU_NOT_RECEIVED:
		pdu->status = ISCSI_PDU_CRC_FAILED;
		break;
	case ISCSI_PDU_CRC_FAILED:
		break;
	case ISCSI_PDU_TIMED_OUT:
		pdu->status = ISCSI_PDU_CRC_FAILED;
		break;
	default:
		return DATAOUT_CANNOT_RECOVER;
	}

recover:
	return iscsit_recover_dataout_sequence(cmd, be32_to_cpu(hdr->offset),
						payload_length);
}