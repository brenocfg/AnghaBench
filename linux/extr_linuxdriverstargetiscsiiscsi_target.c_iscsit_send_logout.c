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
struct iscsi_logout_rsp {int dummy; } ;
struct iscsi_conn {TYPE_1__* conn_transport; } ;
struct iscsi_cmd {int /*<<< orphan*/ * pdu; } ;
struct TYPE_2__ {int (* iscsit_xmit_pdu ) (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int iscsit_build_logout_rsp (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_logout_rsp*) ; 
 int stub1 (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsit_send_logout(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	int rc;

	rc = iscsit_build_logout_rsp(cmd, conn,
			(struct iscsi_logout_rsp *)&cmd->pdu[0]);
	if (rc < 0)
		return rc;

	return conn->conn_transport->iscsit_xmit_pdu(conn, cmd, NULL, NULL, 0);
}