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
struct se_cmd {int /*<<< orphan*/  se_lun; int /*<<< orphan*/  se_dev; } ;
struct xcopy_pt_cmd {int remote_port; struct se_cmd se_cmd; } ;
struct xcopy_op {scalar_t__ op_origin; struct se_cmd* xop_se_cmd; } ;

/* Variables and functions */
 scalar_t__ XCOL_SOURCE_RECV_OP ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void target_xcopy_setup_pt_port(
	struct xcopy_pt_cmd *xpt_cmd,
	struct xcopy_op *xop,
	bool remote_port)
{
	struct se_cmd *ec_cmd = xop->xop_se_cmd;
	struct se_cmd *pt_cmd = &xpt_cmd->se_cmd;

	if (xop->op_origin == XCOL_SOURCE_RECV_OP) {
		/*
		 * Honor destination port reservations for X-COPY PUSH emulation
		 * when CDB is received on local source port, and READs blocks to
		 * WRITE on remote destination port.
		 */
		if (remote_port) {
			xpt_cmd->remote_port = remote_port;
		} else {
			pt_cmd->se_lun = ec_cmd->se_lun;
			pt_cmd->se_dev = ec_cmd->se_dev;

			pr_debug("Honoring local SRC port from ec_cmd->se_dev:"
				" %p\n", pt_cmd->se_dev);
			pt_cmd->se_lun = ec_cmd->se_lun;
			pr_debug("Honoring local SRC port from ec_cmd->se_lun: %p\n",
				pt_cmd->se_lun);
		}
	} else {
		/*
		 * Honor source port reservation for X-COPY PULL emulation
		 * when CDB is received on local desintation port, and READs
		 * blocks from the remote source port to WRITE on local
		 * destination port.
		 */
		if (remote_port) {
			xpt_cmd->remote_port = remote_port;
		} else {
			pt_cmd->se_lun = ec_cmd->se_lun;
			pt_cmd->se_dev = ec_cmd->se_dev;

			pr_debug("Honoring local DST port from ec_cmd->se_dev:"
				" %p\n", pt_cmd->se_dev);
			pt_cmd->se_lun = ec_cmd->se_lun;
			pr_debug("Honoring local DST port from ec_cmd->se_lun: %p\n",
				pt_cmd->se_lun);
		}
	}
}