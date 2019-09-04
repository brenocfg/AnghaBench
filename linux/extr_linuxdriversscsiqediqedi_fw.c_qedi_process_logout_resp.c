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
struct TYPE_10__ {int /*<<< orphan*/  itid; } ;
struct iscsi_logout_response_hdr {int /*<<< orphan*/  time_2_retain; int /*<<< orphan*/  time_2_wait; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  stat_sn; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {struct iscsi_logout_response_hdr logout_response; } ;
struct TYPE_8__ {TYPE_2__ iscsi_hdr; } ;
union iscsi_cqe {TYPE_5__ cqe_solicited; TYPE_3__ cqe_common; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  resp_hdr; } ;
struct qedi_conn {int /*<<< orphan*/  iscsi_conn_id; int /*<<< orphan*/  active_cmd_count; TYPE_4__ gen_pdu; TYPE_1__* cls_conn; } ;
struct qedi_cmd {int io_cmd_in_list; int /*<<< orphan*/  task_id; int /*<<< orphan*/  state; int /*<<< orphan*/  io_cmd; } ;
struct iscsi_task {scalar_t__ dd_data; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; int /*<<< orphan*/  age; } ;
struct iscsi_logout_rsp {void* t2retain; void* t2wait; void* max_cmdsn; void* exp_cmdsn; void* statsn; int /*<<< orphan*/  itt; scalar_t__ hlength; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {struct iscsi_session* session; } ;
struct TYPE_6__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  QEDI_LOG_TID ; 
 int /*<<< orphan*/  RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_itt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct iscsi_logout_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedi_clear_task_idx (struct qedi_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedi_process_logout_resp(struct qedi_ctx *qedi,
				     union iscsi_cqe *cqe,
				     struct iscsi_task *task,
				     struct qedi_conn *qedi_conn)
{
	struct iscsi_conn *conn = qedi_conn->cls_conn->dd_data;
	struct iscsi_logout_rsp *resp_hdr;
	struct iscsi_session *session = conn->session;
	struct iscsi_logout_response_hdr *cqe_logout_response;
	struct qedi_cmd *cmd;

	cmd = (struct qedi_cmd *)task->dd_data;
	cqe_logout_response = &cqe->cqe_common.iscsi_hdr.logout_response;
	spin_lock(&session->back_lock);
	resp_hdr = (struct iscsi_logout_rsp *)&qedi_conn->gen_pdu.resp_hdr;
	memset(resp_hdr, 0, sizeof(struct iscsi_hdr));
	resp_hdr->opcode = cqe_logout_response->opcode;
	resp_hdr->flags = cqe_logout_response->flags;
	resp_hdr->hlength = 0;

	resp_hdr->itt = build_itt(cqe->cqe_solicited.itid, conn->session->age);
	resp_hdr->statsn = cpu_to_be32(cqe_logout_response->stat_sn);
	resp_hdr->exp_cmdsn = cpu_to_be32(cqe_logout_response->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(cqe_logout_response->max_cmd_sn);

	resp_hdr->t2wait = cpu_to_be32(cqe_logout_response->time_2_wait);
	resp_hdr->t2retain = cpu_to_be32(cqe_logout_response->time_2_retain);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_TID,
		  "Freeing tid=0x%x for cid=0x%x\n",
		  cmd->task_id, qedi_conn->iscsi_conn_id);

	if (likely(cmd->io_cmd_in_list)) {
		cmd->io_cmd_in_list = false;
		list_del_init(&cmd->io_cmd);
		qedi_conn->active_cmd_count--;
	} else {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "Active cmd list node already deleted, tid=0x%x, cid=0x%x, io_cmd_node=%p\n",
			  cmd->task_id, qedi_conn->iscsi_conn_id,
			  &cmd->io_cmd);
	}

	cmd->state = RESPONSE_RECEIVED;
	qedi_clear_task_idx(qedi, cmd->task_id);
	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)resp_hdr, NULL, 0);

	spin_unlock(&session->back_lock);
}