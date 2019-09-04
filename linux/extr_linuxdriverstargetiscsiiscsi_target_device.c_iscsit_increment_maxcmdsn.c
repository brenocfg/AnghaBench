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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_session {int /*<<< orphan*/  max_cmd_sn; } ;
struct iscsi_cmd {int maxcmdsn_inc; scalar_t__ immediate_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void iscsit_increment_maxcmdsn(struct iscsi_cmd *cmd, struct iscsi_session *sess)
{
	u32 max_cmd_sn;

	if (cmd->immediate_cmd || cmd->maxcmdsn_inc)
		return;

	cmd->maxcmdsn_inc = 1;

	max_cmd_sn = atomic_inc_return(&sess->max_cmd_sn);
	pr_debug("Updated MaxCmdSN to 0x%08x\n", max_cmd_sn);
}