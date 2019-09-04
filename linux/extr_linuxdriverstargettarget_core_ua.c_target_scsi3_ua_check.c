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
struct se_session {struct se_node_acl* se_node_acl; } ;
struct se_node_acl {int dummy; } ;
struct se_dev_entry {int /*<<< orphan*/  ua_list; } ;
struct se_cmd {int* t_task_cdb; int /*<<< orphan*/  orig_fe_lun; struct se_session* se_sess; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  INQUIRY 130 
#define  REPORT_LUNS 129 
#define  REQUEST_SENSE 128 
 int /*<<< orphan*/  TCM_CHECK_CONDITION_UNIT_ATTENTION ; 
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 

sense_reason_t
target_scsi3_ua_check(struct se_cmd *cmd)
{
	struct se_dev_entry *deve;
	struct se_session *sess = cmd->se_sess;
	struct se_node_acl *nacl;

	if (!sess)
		return 0;

	nacl = sess->se_node_acl;
	if (!nacl)
		return 0;

	rcu_read_lock();
	deve = target_nacl_find_deve(nacl, cmd->orig_fe_lun);
	if (!deve) {
		rcu_read_unlock();
		return 0;
	}
	if (list_empty_careful(&deve->ua_list)) {
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();
	/*
	 * From sam4r14, section 5.14 Unit attention condition:
	 *
	 * a) if an INQUIRY command enters the enabled command state, the
	 *    device server shall process the INQUIRY command and shall neither
	 *    report nor clear any unit attention condition;
	 * b) if a REPORT LUNS command enters the enabled command state, the
	 *    device server shall process the REPORT LUNS command and shall not
	 *    report any unit attention condition;
	 * e) if a REQUEST SENSE command enters the enabled command state while
	 *    a unit attention condition exists for the SCSI initiator port
	 *    associated with the I_T nexus on which the REQUEST SENSE command
	 *    was received, then the device server shall process the command
	 *    and either:
	 */
	switch (cmd->t_task_cdb[0]) {
	case INQUIRY:
	case REPORT_LUNS:
	case REQUEST_SENSE:
		return 0;
	default:
		return TCM_CHECK_CONDITION_UNIT_ATTENTION;
	}
}