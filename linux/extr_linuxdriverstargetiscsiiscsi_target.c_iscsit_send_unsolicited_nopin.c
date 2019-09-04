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
struct iscsi_nopin {int /*<<< orphan*/  ttt; } ;
struct iscsi_conn {TYPE_1__* conn_transport; int /*<<< orphan*/  cid; } ;
struct iscsi_cmd {int /*<<< orphan*/  istate_lock; int /*<<< orphan*/  i_state; int /*<<< orphan*/  stat_sn; int /*<<< orphan*/ * pdu; } ;
struct TYPE_2__ {int (* iscsit_xmit_pdu ) (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISTATE_SENT_NOPIN_WANT_RESPONSE ; 
 int /*<<< orphan*/  ISTATE_SENT_STATUS ; 
 int /*<<< orphan*/  iscsit_build_nopin_rsp (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_nopin*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_send_unsolicited_nopin(
	struct iscsi_cmd *cmd,
	struct iscsi_conn *conn,
	int want_response)
{
	struct iscsi_nopin *hdr = (struct iscsi_nopin *)&cmd->pdu[0];
	int ret;

	iscsit_build_nopin_rsp(cmd, conn, hdr, false);

	pr_debug("Sending Unsolicited NOPIN TTT: 0x%08x StatSN:"
		" 0x%08x CID: %hu\n", hdr->ttt, cmd->stat_sn, conn->cid);

	ret = conn->conn_transport->iscsit_xmit_pdu(conn, cmd, NULL, NULL, 0);
	if (ret < 0)
		return ret;

	spin_lock_bh(&cmd->istate_lock);
	cmd->i_state = want_response ?
		ISTATE_SENT_NOPIN_WANT_RESPONSE : ISTATE_SENT_STATUS;
	spin_unlock_bh(&cmd->istate_lock);

	return 0;
}