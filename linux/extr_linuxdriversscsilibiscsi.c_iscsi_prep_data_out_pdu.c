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
struct iscsi_task {int hdr_len; int /*<<< orphan*/  hdr_itt; int /*<<< orphan*/  lun; struct iscsi_conn* conn; } ;
struct iscsi_r2t_info {unsigned int data_length; unsigned int sent; unsigned int datasn; unsigned int data_offset; unsigned int data_count; int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  ttt; } ;
struct iscsi_data {scalar_t__ flags; int /*<<< orphan*/  dlength; void* offset; int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  itt; int /*<<< orphan*/  lun; int /*<<< orphan*/  opcode; void* datasn; int /*<<< orphan*/  ttt; } ;
struct iscsi_conn {unsigned int max_xmit_dlength; int /*<<< orphan*/  dataout_pdus_cnt; } ;

/* Variables and functions */
 scalar_t__ ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  ISCSI_OP_SCSI_DATA_OUT ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct iscsi_data*,int /*<<< orphan*/ ,int) ; 

void iscsi_prep_data_out_pdu(struct iscsi_task *task, struct iscsi_r2t_info *r2t,
			   struct iscsi_data *hdr)
{
	struct iscsi_conn *conn = task->conn;
	unsigned int left = r2t->data_length - r2t->sent;

	task->hdr_len = sizeof(struct iscsi_data);

	memset(hdr, 0, sizeof(struct iscsi_data));
	hdr->ttt = r2t->ttt;
	hdr->datasn = cpu_to_be32(r2t->datasn);
	r2t->datasn++;
	hdr->opcode = ISCSI_OP_SCSI_DATA_OUT;
	hdr->lun = task->lun;
	hdr->itt = task->hdr_itt;
	hdr->exp_statsn = r2t->exp_statsn;
	hdr->offset = cpu_to_be32(r2t->data_offset + r2t->sent);
	if (left > conn->max_xmit_dlength) {
		hton24(hdr->dlength, conn->max_xmit_dlength);
		r2t->data_count = conn->max_xmit_dlength;
		hdr->flags = 0;
	} else {
		hton24(hdr->dlength, left);
		r2t->data_count = left;
		hdr->flags = ISCSI_FLAG_CMD_FINAL;
	}
	conn->dataout_pdus_cnt++;
}