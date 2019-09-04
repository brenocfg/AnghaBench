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
struct iscsi_reject {int /*<<< orphan*/  reason; int /*<<< orphan*/  statsn; } ;
struct iscsi_conn {TYPE_1__* conn_transport; int /*<<< orphan*/  cid; } ;
struct iscsi_cmd {int /*<<< orphan*/  buf_ptr; int /*<<< orphan*/ * pdu; } ;
struct TYPE_2__ {int (* iscsit_xmit_pdu ) (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_HDR_LEN ; 
 int /*<<< orphan*/  iscsit_build_reject (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_reject*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_send_reject(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn)
{
	struct iscsi_reject *hdr = (struct iscsi_reject *)&cmd->pdu[0];

	iscsit_build_reject(cmd, conn, hdr);

	pr_debug("Built Reject PDU StatSN: 0x%08x, Reason: 0x%02x,"
		" CID: %hu\n", ntohl(hdr->statsn), hdr->reason, conn->cid);

	return conn->conn_transport->iscsit_xmit_pdu(conn, cmd, NULL,
						     cmd->buf_ptr,
						     ISCSI_HDR_LEN);
}