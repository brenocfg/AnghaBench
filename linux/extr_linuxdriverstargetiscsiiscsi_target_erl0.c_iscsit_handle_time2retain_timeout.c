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
struct timer_list {int dummy; } ;
struct se_portal_group {int /*<<< orphan*/  session_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cxn_timeout_errors; int /*<<< orphan*/  last_sess_failure_type; int /*<<< orphan*/  last_sess_fail_rem_name; } ;
struct iscsi_tiqn {TYPE_2__ sess_err_stats; } ;
struct iscsi_session {int time2retain_timer_flags; int /*<<< orphan*/  conn_timeout_errors; TYPE_1__* sess_ops; int /*<<< orphan*/  sid; int /*<<< orphan*/  session_reinstatement; struct iscsi_portal_group* tpg; } ;
struct iscsi_portal_group {struct iscsi_tiqn* tpg_tiqn; struct se_portal_group tpg_se_tpg; } ;
struct TYPE_3__ {scalar_t__ InitiatorName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESS_ERR_CXN_TIMEOUT ; 
 int ISCSI_TF_EXPIRED ; 
 int ISCSI_TF_STOP ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct iscsi_session* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_close_session (struct iscsi_session*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct iscsi_session* sess ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  time2retain_timer ; 

void iscsit_handle_time2retain_timeout(struct timer_list *t)
{
	struct iscsi_session *sess = from_timer(sess, t, time2retain_timer);
	struct iscsi_portal_group *tpg = sess->tpg;
	struct se_portal_group *se_tpg = &tpg->tpg_se_tpg;

	spin_lock_bh(&se_tpg->session_lock);
	if (sess->time2retain_timer_flags & ISCSI_TF_STOP) {
		spin_unlock_bh(&se_tpg->session_lock);
		return;
	}
	if (atomic_read(&sess->session_reinstatement)) {
		pr_err("Exiting Time2Retain handler because"
				" session_reinstatement=1\n");
		spin_unlock_bh(&se_tpg->session_lock);
		return;
	}
	sess->time2retain_timer_flags |= ISCSI_TF_EXPIRED;

	pr_err("Time2Retain timer expired for SID: %u, cleaning up"
			" iSCSI session.\n", sess->sid);
	{
	struct iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	if (tiqn) {
		spin_lock(&tiqn->sess_err_stats.lock);
		strcpy(tiqn->sess_err_stats.last_sess_fail_rem_name,
			(void *)sess->sess_ops->InitiatorName);
		tiqn->sess_err_stats.last_sess_failure_type =
				ISCSI_SESS_ERR_CXN_TIMEOUT;
		tiqn->sess_err_stats.cxn_timeout_errors++;
		atomic_long_inc(&sess->conn_timeout_errors);
		spin_unlock(&tiqn->sess_err_stats.lock);
	}
	}

	spin_unlock_bh(&se_tpg->session_lock);
	iscsit_close_session(sess);
}