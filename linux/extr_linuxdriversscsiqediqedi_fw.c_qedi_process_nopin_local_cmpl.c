#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_conn {TYPE_1__* cls_conn; } ;
struct qedi_cmd {int /*<<< orphan*/  task_id; int /*<<< orphan*/  state; } ;
struct iscsi_task {struct qedi_cmd* dd_data; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; } ;
struct iscsi_cqe_solicited {int /*<<< orphan*/  itid; } ;
struct iscsi_conn {struct iscsi_session* session; } ;
struct TYPE_2__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_UNSOL ; 
 int /*<<< orphan*/  RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  __iscsi_put_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  qedi_clear_task_idx (struct qedi_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedi_process_nopin_local_cmpl(struct qedi_ctx *qedi,
					  struct iscsi_cqe_solicited *cqe,
					  struct iscsi_task *task,
					  struct qedi_conn *qedi_conn)
{
	struct iscsi_conn *conn = qedi_conn->cls_conn->dd_data;
	struct iscsi_session *session = conn->session;
	struct qedi_cmd *cmd = task->dd_data;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_UNSOL,
		  "itid=0x%x, cmd task id=0x%x\n",
		  cqe->itid, cmd->task_id);

	cmd->state = RESPONSE_RECEIVED;
	qedi_clear_task_idx(qedi, cmd->task_id);

	spin_lock_bh(&session->back_lock);
	__iscsi_put_task(task);
	spin_unlock_bh(&session->back_lock);
}