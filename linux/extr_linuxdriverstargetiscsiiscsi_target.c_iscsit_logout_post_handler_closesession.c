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
struct iscsi_session {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  conn_logout_comp; int /*<<< orphan*/  conn_logout_remove; int /*<<< orphan*/  tx_thread_active; TYPE_1__* conn_transport; struct iscsi_session* sess; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdma_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_close_session (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsit_dec_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_dec_session_usage_count (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsit_stop_session (struct iscsi_session*,int,int) ; 

__attribute__((used)) static void iscsit_logout_post_handler_closesession(
	struct iscsi_conn *conn)
{
	struct iscsi_session *sess = conn->sess;
	int sleep = 1;
	/*
	 * Traditional iscsi/tcp will invoke this logic from TX thread
	 * context during session logout, so clear tx_thread_active and
	 * sleep if iscsit_close_connection() has not already occured.
	 *
	 * Since iser-target invokes this logic from it's own workqueue,
	 * always sleep waiting for RX/TX thread shutdown to complete
	 * within iscsit_close_connection().
	 */
	if (!conn->conn_transport->rdma_shutdown) {
		sleep = cmpxchg(&conn->tx_thread_active, true, false);
		if (!sleep)
			return;
	}

	atomic_set(&conn->conn_logout_remove, 0);
	complete(&conn->conn_logout_comp);

	iscsit_dec_conn_usage_count(conn);
	iscsit_stop_session(sess, sleep, sleep);
	iscsit_dec_session_usage_count(sess);
	iscsit_close_session(sess);
}