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
struct qedi_work_map {int dummy; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_conn {int /*<<< orphan*/  iscsi_conn_id; int /*<<< orphan*/  wait_queue; } ;
struct qedi_cmd {scalar_t__ state; scalar_t__ type; int /*<<< orphan*/  task_id; } ;
struct iscsi_task {scalar_t__ dd_data; } ;

/* Variables and functions */
 scalar_t__ CLEANUP_RECV ; 
 scalar_t__ CLEANUP_WAIT_FAILED ; 
 int HZ ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_SCSI_TM ; 
 scalar_t__ RESPONSE_RECEIVED ; 
 scalar_t__ TYPEIO ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qedi_wait_for_cleanup_request(struct qedi_ctx *qedi,
					 struct qedi_conn *qedi_conn,
					 struct iscsi_task *task,
					 struct qedi_cmd *qedi_cmd,
					 struct qedi_work_map *list_work)
{
	struct qedi_cmd *cmd = (struct qedi_cmd *)task->dd_data;
	int wait;

	wait  = wait_event_interruptible_timeout(qedi_conn->wait_queue,
						 ((qedi_cmd->state ==
						   CLEANUP_RECV) ||
						 ((qedi_cmd->type == TYPEIO) &&
						  (cmd->state ==
						   RESPONSE_RECEIVED))),
						 5 * HZ);
	if (!wait) {
		qedi_cmd->state = CLEANUP_WAIT_FAILED;

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_SCSI_TM,
			  "Cleanup timedout tid=0x%x, issue connection recovery, cid=0x%x\n",
			  cmd->task_id, qedi_conn->iscsi_conn_id);

		return -1;
	}
	return 0;
}