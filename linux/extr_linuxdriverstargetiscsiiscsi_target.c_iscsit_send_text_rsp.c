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
struct iscsi_text_rsp {int dummy; } ;
struct iscsi_conn {TYPE_1__* conn_transport; } ;
struct iscsi_cmd {int /*<<< orphan*/  buf_ptr; scalar_t__ pdu; } ;
struct TYPE_2__ {int (* iscsit_xmit_pdu ) (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  transport_type; } ;

/* Variables and functions */
 int iscsit_build_text_rsp (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_text_rsp*,int /*<<< orphan*/ ) ; 
 int stub1 (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iscsit_send_text_rsp(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn)
{
	struct iscsi_text_rsp *hdr = (struct iscsi_text_rsp *)cmd->pdu;
	int text_length;

	text_length = iscsit_build_text_rsp(cmd, conn, hdr,
				conn->conn_transport->transport_type);
	if (text_length < 0)
		return text_length;

	return conn->conn_transport->iscsit_xmit_pdu(conn, cmd, NULL,
						     cmd->buf_ptr,
						     text_length);
}