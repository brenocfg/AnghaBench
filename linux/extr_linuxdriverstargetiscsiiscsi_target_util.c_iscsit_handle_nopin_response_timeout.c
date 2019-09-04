#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cxn_timeout_errors; int /*<<< orphan*/  last_sess_failure_type; int /*<<< orphan*/  last_sess_fail_rem_name; } ;
struct iscsi_tiqn {TYPE_3__ sess_err_stats; } ;
struct iscsi_portal_group {struct iscsi_tiqn* tpg_tiqn; } ;
struct iscsi_conn {int nopin_response_timer_flags; TYPE_2__* sess; int /*<<< orphan*/  nopin_timer_lock; int /*<<< orphan*/  cid; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn_timeout_errors; TYPE_1__* sess_ops; struct iscsi_portal_group* tpg; int /*<<< orphan*/  sid; } ;
struct TYPE_4__ {int /*<<< orphan*/  InitiatorName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESS_ERR_CXN_TIMEOUT ; 
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct iscsi_conn* conn ; 
 struct iscsi_conn* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_cause_connection_reinstatement (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_dec_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_inc_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  nopin_response_timer ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iscsit_handle_nopin_response_timeout(struct timer_list *t)
{
	struct iscsi_conn *conn = from_timer(conn, t, nopin_response_timer);

	iscsit_inc_conn_usage_count(conn);

	spin_lock_bh(&conn->nopin_timer_lock);
	if (conn->nopin_response_timer_flags & ISCSI_TF_STOP) {
		spin_unlock_bh(&conn->nopin_timer_lock);
		iscsit_dec_conn_usage_count(conn);
		return;
	}

	pr_debug("Did not receive response to NOPIN on CID: %hu on"
		" SID: %u, failing connection.\n", conn->cid,
			conn->sess->sid);
	conn->nopin_response_timer_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_timer_lock);

	{
	struct iscsi_portal_group *tpg = conn->sess->tpg;
	struct iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	if (tiqn) {
		spin_lock_bh(&tiqn->sess_err_stats.lock);
		strcpy(tiqn->sess_err_stats.last_sess_fail_rem_name,
				conn->sess->sess_ops->InitiatorName);
		tiqn->sess_err_stats.last_sess_failure_type =
				ISCSI_SESS_ERR_CXN_TIMEOUT;
		tiqn->sess_err_stats.cxn_timeout_errors++;
		atomic_long_inc(&conn->sess->conn_timeout_errors);
		spin_unlock_bh(&tiqn->sess_err_stats.lock);
	}
	}

	iscsit_cause_connection_reinstatement(conn, 0);
	iscsit_dec_conn_usage_count(conn);
}