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
struct iscsi_session {scalar_t__ state; int /*<<< orphan*/  frwd_lock; } ;
struct iscsi_conn {scalar_t__ stop_stage; int /*<<< orphan*/  cls_conn; int /*<<< orphan*/  suspend_rx; int /*<<< orphan*/  suspend_tx; struct iscsi_session* session; } ;
typedef  enum iscsi_err { ____Placeholder_iscsi_err } iscsi_err ;

/* Variables and functions */
 scalar_t__ ISCSI_STATE_FAILED ; 
 int /*<<< orphan*/  ISCSI_SUSPEND_BIT ; 
 int /*<<< orphan*/  iscsi_conn_error_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsi_conn_failure(struct iscsi_conn *conn, enum iscsi_err err)
{
	struct iscsi_session *session = conn->session;

	spin_lock_bh(&session->frwd_lock);
	if (session->state == ISCSI_STATE_FAILED) {
		spin_unlock_bh(&session->frwd_lock);
		return;
	}

	if (conn->stop_stage == 0)
		session->state = ISCSI_STATE_FAILED;
	spin_unlock_bh(&session->frwd_lock);

	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	set_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx);
	iscsi_conn_error_event(conn->cls_conn, err);
}