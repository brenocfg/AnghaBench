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
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_task {int /*<<< orphan*/  itt; struct iscsi_conn* conn; } ;
struct iscsi_conn {int /*<<< orphan*/  session; int /*<<< orphan*/  last_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_SESSION (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_TASK_COMPLETED ; 
 int /*<<< orphan*/  __iscsi_update_cmdsn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_complete_task (struct iscsi_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

void iscsi_complete_scsi_task(struct iscsi_task *task,
			      uint32_t exp_cmdsn, uint32_t max_cmdsn)
{
	struct iscsi_conn *conn = task->conn;

	ISCSI_DBG_SESSION(conn->session, "[itt 0x%x]\n", task->itt);

	conn->last_recv = jiffies;
	__iscsi_update_cmdsn(conn->session, exp_cmdsn, max_cmdsn);
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
}