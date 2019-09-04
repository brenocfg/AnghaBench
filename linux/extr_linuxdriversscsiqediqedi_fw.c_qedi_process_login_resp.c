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
struct TYPE_9__ {int /*<<< orphan*/  itid; } ;
struct iscsi_login_response_hdr {int hdr_second_dword; int /*<<< orphan*/  status_detail; int /*<<< orphan*/  status_class; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  stat_sn; int /*<<< orphan*/  tsih; int /*<<< orphan*/  flags_attr; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {struct iscsi_login_response_hdr login_response; } ;
struct TYPE_8__ {TYPE_2__ iscsi_hdr; } ;
union iscsi_cqe {TYPE_4__ cqe_solicited; TYPE_3__ cqe_common; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  tasks; } ;
struct TYPE_10__ {scalar_t__ resp_buf; scalar_t__ resp_wr_ptr; int /*<<< orphan*/  resp_hdr; } ;
struct qedi_conn {int /*<<< orphan*/  iscsi_conn_id; TYPE_5__ gen_pdu; int /*<<< orphan*/  active_cmd_count; TYPE_1__* cls_conn; } ;
struct qedi_cmd {int io_cmd_in_list; int /*<<< orphan*/  task_id; int /*<<< orphan*/  state; int /*<<< orphan*/  io_cmd; } ;
struct iscsi_task {scalar_t__ dd_data; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; int /*<<< orphan*/  age; } ;
struct iscsi_login_rsp {int /*<<< orphan*/  status_detail; int /*<<< orphan*/  status_class; void* max_cmdsn; void* exp_cmdsn; void* statsn; int /*<<< orphan*/  tsih; int /*<<< orphan*/  itt; int /*<<< orphan*/  dlength; scalar_t__ hlength; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {struct iscsi_session* session; } ;
struct e4_iscsi_task_context {int /*<<< orphan*/  status_detail; int /*<<< orphan*/  status_class; void* max_cmdsn; void* exp_cmdsn; void* statsn; int /*<<< orphan*/  tsih; int /*<<< orphan*/  itt; int /*<<< orphan*/  dlength; scalar_t__ hlength; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int ISCSI_LOGIN_RESPONSE_HDR_DATA_SEG_LEN_MASK ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_TID ; 
 int /*<<< orphan*/  RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_itt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct iscsi_login_rsp*,char,int) ; 
 int /*<<< orphan*/  qedi_clear_task_idx (struct qedi_ctx*,int /*<<< orphan*/ ) ; 
 struct iscsi_login_rsp* qedi_get_task_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedi_process_login_resp(struct qedi_ctx *qedi,
				    union iscsi_cqe *cqe,
				    struct iscsi_task *task,
				    struct qedi_conn *qedi_conn)
{
	struct iscsi_conn *conn = qedi_conn->cls_conn->dd_data;
	struct iscsi_session *session = conn->session;
	struct e4_iscsi_task_context *task_ctx;
	struct iscsi_login_rsp *resp_hdr_ptr;
	struct iscsi_login_response_hdr *cqe_login_response;
	struct qedi_cmd *cmd;
	int pld_len;

	cmd = (struct qedi_cmd *)task->dd_data;

	cqe_login_response = &cqe->cqe_common.iscsi_hdr.login_response;
	task_ctx = qedi_get_task_mem(&qedi->tasks, cmd->task_id);

	spin_lock(&session->back_lock);
	resp_hdr_ptr =  (struct iscsi_login_rsp *)&qedi_conn->gen_pdu.resp_hdr;
	memset(resp_hdr_ptr, 0, sizeof(struct iscsi_login_rsp));
	resp_hdr_ptr->opcode = cqe_login_response->opcode;
	resp_hdr_ptr->flags = cqe_login_response->flags_attr;
	resp_hdr_ptr->hlength = 0;

	hton24(resp_hdr_ptr->dlength,
	       (cqe_login_response->hdr_second_dword &
		ISCSI_LOGIN_RESPONSE_HDR_DATA_SEG_LEN_MASK));
	resp_hdr_ptr->itt = build_itt(cqe->cqe_solicited.itid,
				      conn->session->age);
	resp_hdr_ptr->tsih = cqe_login_response->tsih;
	resp_hdr_ptr->statsn = cpu_to_be32(cqe_login_response->stat_sn);
	resp_hdr_ptr->exp_cmdsn = cpu_to_be32(cqe_login_response->exp_cmd_sn);
	resp_hdr_ptr->max_cmdsn = cpu_to_be32(cqe_login_response->max_cmd_sn);
	resp_hdr_ptr->status_class = cqe_login_response->status_class;
	resp_hdr_ptr->status_detail = cqe_login_response->status_detail;
	pld_len = cqe_login_response->hdr_second_dword &
		  ISCSI_LOGIN_RESPONSE_HDR_DATA_SEG_LEN_MASK;
	qedi_conn->gen_pdu.resp_wr_ptr = qedi_conn->gen_pdu.resp_buf + pld_len;

	if (likely(cmd->io_cmd_in_list)) {
		cmd->io_cmd_in_list = false;
		list_del_init(&cmd->io_cmd);
		qedi_conn->active_cmd_count--;
	}

	memset(task_ctx, '\0', sizeof(*task_ctx));

	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)resp_hdr_ptr,
			     qedi_conn->gen_pdu.resp_buf,
			     (qedi_conn->gen_pdu.resp_wr_ptr -
			     qedi_conn->gen_pdu.resp_buf));

	spin_unlock(&session->back_lock);
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_TID,
		  "Freeing tid=0x%x for cid=0x%x\n",
		  cmd->task_id, qedi_conn->iscsi_conn_id);
	cmd->state = RESPONSE_RECEIVED;
	qedi_clear_task_idx(qedi, cmd->task_id);
}