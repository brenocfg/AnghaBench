#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct se_node_acl {scalar_t__ queue_depth; } ;
struct iscsi_session {int /*<<< orphan*/  max_cmd_sn; scalar_t__ cmdsn_window; TYPE_2__* se_sess; TYPE_1__* sess_ops; } ;
struct TYPE_4__ {struct se_node_acl* se_node_acl; } ;
struct TYPE_3__ {scalar_t__ SessionType; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 

void iscsit_determine_maxcmdsn(struct iscsi_session *sess)
{
	struct se_node_acl *se_nacl;

	/*
	 * This is a discovery session, the single queue slot was already
	 * assigned in iscsi_login_zero_tsih().  Since only Logout and
	 * Text Opcodes are allowed during discovery we do not have to worry
	 * about the HBA's queue depth here.
	 */
	if (sess->sess_ops->SessionType)
		return;

	se_nacl = sess->se_sess->se_node_acl;

	/*
	 * This is a normal session, set the Session's CmdSN window to the
	 * struct se_node_acl->queue_depth.  The value in struct se_node_acl->queue_depth
	 * has already been validated as a legal value in
	 * core_set_queue_depth_for_node().
	 */
	sess->cmdsn_window = se_nacl->queue_depth;
	atomic_add(se_nacl->queue_depth - 1, &sess->max_cmd_sn);
}