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
struct qeth_cmd_buffer {int /*<<< orphan*/  data; int /*<<< orphan*/  callback; TYPE_1__* channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdu_hdr_ack; int /*<<< orphan*/  pdu_hdr; int /*<<< orphan*/  trans_hdr; } ;
struct qeth_card {TYPE_2__ seqno; } ;
struct TYPE_3__ {int /*<<< orphan*/  ccw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_WRITE ; 
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  QETH_DBF_CTRL_LEN ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_PDU_HEADER_ACK_SEQ_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_PDU_HEADER_SEQ_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_SEQ_NO_LENGTH ; 
 int /*<<< orphan*/  QETH_TRANSPORT_HEADER_SEQ_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_release_buffer ; 
 int /*<<< orphan*/  qeth_setup_ccw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void qeth_prepare_control_data(struct qeth_card *card, int len,
		struct qeth_cmd_buffer *iob)
{
	qeth_setup_ccw(iob->channel->ccw, CCW_CMD_WRITE, len, iob->data);
	iob->callback = qeth_release_buffer;

	memcpy(QETH_TRANSPORT_HEADER_SEQ_NO(iob->data),
	       &card->seqno.trans_hdr, QETH_SEQ_NO_LENGTH);
	card->seqno.trans_hdr++;
	memcpy(QETH_PDU_HEADER_SEQ_NO(iob->data),
	       &card->seqno.pdu_hdr, QETH_SEQ_NO_LENGTH);
	card->seqno.pdu_hdr++;
	memcpy(QETH_PDU_HEADER_ACK_SEQ_NO(iob->data),
	       &card->seqno.pdu_hdr_ack, QETH_SEQ_NO_LENGTH);
	QETH_DBF_HEX(CTRL, 2, iob->data, QETH_DBF_CTRL_LEN);
}