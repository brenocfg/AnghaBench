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
typedef  int /*<<< orphan*/  u8 ;
struct se_tmr_req {int /*<<< orphan*/  ref_task_tag; int /*<<< orphan*/  function; } ;
struct se_cmd {int se_cmd_flags; int /*<<< orphan*/  cmd_kref; int /*<<< orphan*/  t_state; TYPE_1__* se_tfo; int /*<<< orphan*/  tag; int /*<<< orphan*/  data_length; int /*<<< orphan*/  data_direction; struct se_tmr_req* se_tmr_req; int /*<<< orphan*/ * t_task_cdb; int /*<<< orphan*/  transport_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_cmd_state ) (struct se_cmd*) ;} ;

/* Variables and functions */
 int SCF_SCSI_TMR_CDB ; 
 int /*<<< orphan*/  cmd_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_dir_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*) ; 
 int /*<<< orphan*/  target_tmf_name (int /*<<< orphan*/ ) ; 
 char* target_ts_to_str (int /*<<< orphan*/ ) ; 

void target_show_cmd(const char *pfx, struct se_cmd *cmd)
{
	char *ts_str = target_ts_to_str(cmd->transport_state);
	const u8 *cdb = cmd->t_task_cdb;
	struct se_tmr_req *tmf = cmd->se_tmr_req;

	if (!(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)) {
		pr_debug("%scmd %#02x:%#02x with tag %#llx dir %s i_state %d t_state %s len %d refcnt %d transport_state %s\n",
			 pfx, cdb[0], cdb[1], cmd->tag,
			 data_dir_name(cmd->data_direction),
			 cmd->se_tfo->get_cmd_state(cmd),
			 cmd_state_name(cmd->t_state), cmd->data_length,
			 kref_read(&cmd->cmd_kref), ts_str);
	} else {
		pr_debug("%stmf %s with tag %#llx ref_task_tag %#llx i_state %d t_state %s refcnt %d transport_state %s\n",
			 pfx, target_tmf_name(tmf->function), cmd->tag,
			 tmf->ref_task_tag, cmd->se_tfo->get_cmd_state(cmd),
			 cmd_state_name(cmd->t_state),
			 kref_read(&cmd->cmd_kref), ts_str);
	}
	kfree(ts_str);
}