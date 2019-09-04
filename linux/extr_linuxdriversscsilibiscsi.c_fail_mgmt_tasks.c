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
struct iscsi_task {scalar_t__ state; int /*<<< orphan*/  itt; scalar_t__ sc; } ;
struct iscsi_session {int dummy; } ;
struct iscsi_conn {TYPE_1__* session; } ;
struct TYPE_2__ {int cmds_max; struct iscsi_task** cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_SESSION (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ISCSI_TASK_ABRT_SESS_RECOV ; 
 int ISCSI_TASK_COMPLETED ; 
 scalar_t__ ISCSI_TASK_FREE ; 
 scalar_t__ ISCSI_TASK_PENDING ; 
 int /*<<< orphan*/  iscsi_complete_task (struct iscsi_task*,int) ; 

__attribute__((used)) static void
fail_mgmt_tasks(struct iscsi_session *session, struct iscsi_conn *conn)
{
	struct iscsi_task *task;
	int i, state;

	for (i = 0; i < conn->session->cmds_max; i++) {
		task = conn->session->cmds[i];
		if (task->sc)
			continue;

		if (task->state == ISCSI_TASK_FREE)
			continue;

		ISCSI_DBG_SESSION(conn->session,
				  "failing mgmt itt 0x%x state %d\n",
				  task->itt, task->state);
		state = ISCSI_TASK_ABRT_SESS_RECOV;
		if (task->state == ISCSI_TASK_PENDING)
			state = ISCSI_TASK_COMPLETED;
		iscsi_complete_task(task, state);

	}
}