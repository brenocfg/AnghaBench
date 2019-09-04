#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iscsi_task {scalar_t__ hdr; struct bnx2i_cmd* dd_data; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; } ;
struct iscsi_scsi_rsp {scalar_t__ opcode; scalar_t__ cmd_status; void* residual_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  response; void* exp_cmdsn; void* max_cmdsn; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  data; int /*<<< orphan*/  txdata_octets; int /*<<< orphan*/  r2t_pdus_cnt; int /*<<< orphan*/  dataout_pdus_cnt; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  datain_pdus_cnt; } ;
struct cqe {int dummy; } ;
struct bnx2i_hba {int dummy; } ;
struct bnx2i_conn {struct bnx2i_hba* hba; TYPE_1__* cls_conn; } ;
struct TYPE_9__ {scalar_t__ num_r2ts; scalar_t__ num_data_outs; } ;
struct TYPE_7__ {scalar_t__ num_data_ins; } ;
struct TYPE_10__ {TYPE_4__ write_stat; TYPE_2__ read_stat; } ;
struct bnx2i_cmd_response {int itt; scalar_t__ op_code; scalar_t__ status; int data_length; int /*<<< orphan*/  residual_count; int /*<<< orphan*/  response_flags; int /*<<< orphan*/  response; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  max_cmd_sn; TYPE_5__ task_stat; } ;
struct TYPE_8__ {int op_attr; scalar_t__ total_data_transfer_length; } ;
struct bnx2i_cmd {int /*<<< orphan*/  conn; TYPE_3__ req; } ;
struct TYPE_6__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STATS_64 (struct bnx2i_hba*,int /*<<< orphan*/ ,scalar_t__) ; 
 int BNX2I_RQ_WQE_SIZE ; 
 int ISCSI_CMD_REQUEST_READ ; 
 int ISCSI_CMD_RESPONSE_INDEX ; 
 int ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 scalar_t__ ISCSI_OP_SCSI_DATA_IN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2i_get_rq_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2i_iscsi_unmap_sg_list (struct bnx2i_cmd*) ; 
 int /*<<< orphan*/  bnx2i_put_rq_buf (int /*<<< orphan*/ ,int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_pdus ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_pdus ; 

int bnx2i_process_scsi_cmd_resp(struct iscsi_session *session,
				struct bnx2i_conn *bnx2i_conn,
				struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct bnx2i_hba *hba = bnx2i_conn->hba;
	struct bnx2i_cmd_response *resp_cqe;
	struct bnx2i_cmd *bnx2i_cmd;
	struct iscsi_task *task;
	struct iscsi_scsi_rsp *hdr;
	u32 datalen = 0;

	resp_cqe = (struct bnx2i_cmd_response *)cqe;
	spin_lock_bh(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 resp_cqe->itt & ISCSI_CMD_RESPONSE_INDEX);
	if (!task)
		goto fail;

	bnx2i_cmd = task->dd_data;

	if (bnx2i_cmd->req.op_attr & ISCSI_CMD_REQUEST_READ) {
		conn->datain_pdus_cnt +=
			resp_cqe->task_stat.read_stat.num_data_ins;
		conn->rxdata_octets +=
			bnx2i_cmd->req.total_data_transfer_length;
		ADD_STATS_64(hba, rx_pdus,
			     resp_cqe->task_stat.read_stat.num_data_ins);
		ADD_STATS_64(hba, rx_bytes,
			     bnx2i_cmd->req.total_data_transfer_length);
	} else {
		conn->dataout_pdus_cnt +=
			resp_cqe->task_stat.write_stat.num_data_outs;
		conn->r2t_pdus_cnt +=
			resp_cqe->task_stat.write_stat.num_r2ts;
		conn->txdata_octets +=
			bnx2i_cmd->req.total_data_transfer_length;
		ADD_STATS_64(hba, tx_pdus,
			     resp_cqe->task_stat.write_stat.num_data_outs);
		ADD_STATS_64(hba, tx_bytes,
			     bnx2i_cmd->req.total_data_transfer_length);
		ADD_STATS_64(hba, rx_pdus,
			     resp_cqe->task_stat.write_stat.num_r2ts);
	}
	bnx2i_iscsi_unmap_sg_list(bnx2i_cmd);

	hdr = (struct iscsi_scsi_rsp *)task->hdr;
	resp_cqe = (struct bnx2i_cmd_response *)cqe;
	hdr->opcode = resp_cqe->op_code;
	hdr->max_cmdsn = cpu_to_be32(resp_cqe->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(resp_cqe->exp_cmd_sn);
	hdr->response = resp_cqe->response;
	hdr->cmd_status = resp_cqe->status;
	hdr->flags = resp_cqe->response_flags;
	hdr->residual_count = cpu_to_be32(resp_cqe->residual_count);

	if (resp_cqe->op_code == ISCSI_OP_SCSI_DATA_IN)
		goto done;

	if (resp_cqe->status == SAM_STAT_CHECK_CONDITION) {
		datalen = resp_cqe->data_length;
		if (datalen < 2)
			goto done;

		if (datalen > BNX2I_RQ_WQE_SIZE) {
			iscsi_conn_printk(KERN_ERR, conn,
					  "sense data len %d > RQ sz\n",
					  datalen);
			datalen = BNX2I_RQ_WQE_SIZE;
		} else if (datalen > ISCSI_DEF_MAX_RECV_SEG_LEN) {
			iscsi_conn_printk(KERN_ERR, conn,
					  "sense data len %d > conn data\n",
					  datalen);
			datalen = ISCSI_DEF_MAX_RECV_SEG_LEN;
		}

		bnx2i_get_rq_buf(bnx2i_cmd->conn, conn->data, datalen);
		bnx2i_put_rq_buf(bnx2i_cmd->conn, 1);
	}

done:
	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)hdr,
			     conn->data, datalen);
fail:
	spin_unlock_bh(&session->back_lock);
	return 0;
}