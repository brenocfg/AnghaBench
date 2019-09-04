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
struct iscsi_conn {int /*<<< orphan*/  transport_failed; TYPE_1__* conn_transport; int /*<<< orphan*/  rx_login_comp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iscsit_get_rx_pdu ) (struct iscsi_conn*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ iscsi_target_check_conn_state (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_take_action_for_connection_exit (struct iscsi_conn*,int*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_conn*) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int iscsi_target_rx_thread(void *arg)
{
	int rc;
	struct iscsi_conn *conn = arg;
	bool conn_freed = false;

	/*
	 * Allow ourselves to be interrupted by SIGINT so that a
	 * connection recovery / failure event can be triggered externally.
	 */
	allow_signal(SIGINT);
	/*
	 * Wait for iscsi_post_login_handler() to complete before allowing
	 * incoming iscsi/tcp socket I/O, and/or failing the connection.
	 */
	rc = wait_for_completion_interruptible(&conn->rx_login_comp);
	if (rc < 0 || iscsi_target_check_conn_state(conn))
		goto out;

	if (!conn->conn_transport->iscsit_get_rx_pdu)
		return 0;

	conn->conn_transport->iscsit_get_rx_pdu(conn);

	if (!signal_pending(current))
		atomic_set(&conn->transport_failed, 1);
	iscsit_take_action_for_connection_exit(conn, &conn_freed);

out:
	if (!conn_freed) {
		while (!kthread_should_stop()) {
			msleep(100);
		}
	}

	return 0;
}