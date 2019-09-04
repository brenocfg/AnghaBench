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
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct qlogicfas408_priv {scalar_t__ qinitid; int /*<<< orphan*/ * qlcmd; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct qlogicfas408_priv* get_priv_by_cmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ql_icmd (struct scsi_cmnd*) ; 
 scalar_t__ scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int qlogicfas408_queuecommand_lck(struct scsi_cmnd *cmd,
			      void (*done) (struct scsi_cmnd *))
{
	struct qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	if (scmd_id(cmd) == priv->qinitid) {
		cmd->result = DID_BAD_TARGET << 16;
		done(cmd);
		return 0;
	}

	cmd->scsi_done = done;
	/* wait for the last command's interrupt to finish */
	while (priv->qlcmd != NULL) {
		barrier();
		cpu_relax();
	}
	ql_icmd(cmd);
	return 0;
}