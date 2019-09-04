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
struct iscsi_conn {scalar_t__ conn_state; int /*<<< orphan*/  queues_wq; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ TARG_CONN_STATE_IN_LOGIN ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  iscsit_conn_all_queues_empty (struct iscsi_conn*) ; 
 int iscsit_handle_immediate_queue (struct iscsi_conn*) ; 
 int iscsit_handle_response_queue (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_take_action_for_connection_exit (struct iscsi_conn*,int*) ; 
 int /*<<< orphan*/  iscsit_thread_check_cpumask (struct iscsi_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int iscsi_target_tx_thread(void *arg)
{
	int ret = 0;
	struct iscsi_conn *conn = arg;
	bool conn_freed = false;

	/*
	 * Allow ourselves to be interrupted by SIGINT so that a
	 * connection recovery / failure event can be triggered externally.
	 */
	allow_signal(SIGINT);

	while (!kthread_should_stop()) {
		/*
		 * Ensure that both TX and RX per connection kthreads
		 * are scheduled to run on the same CPU.
		 */
		iscsit_thread_check_cpumask(conn, current, 1);

		wait_event_interruptible(conn->queues_wq,
					 !iscsit_conn_all_queues_empty(conn));

		if (signal_pending(current))
			goto transport_err;

get_immediate:
		ret = iscsit_handle_immediate_queue(conn);
		if (ret < 0)
			goto transport_err;

		ret = iscsit_handle_response_queue(conn);
		if (ret == 1) {
			goto get_immediate;
		} else if (ret == -ECONNRESET) {
			conn_freed = true;
			goto out;
		} else if (ret < 0) {
			goto transport_err;
		}
	}

transport_err:
	/*
	 * Avoid the normal connection failure code-path if this connection
	 * is still within LOGIN mode, and iscsi_np process context is
	 * responsible for cleaning up the early connection failure.
	 */
	if (conn->conn_state != TARG_CONN_STATE_IN_LOGIN)
		iscsit_take_action_for_connection_exit(conn, &conn_freed);
out:
	if (!conn_freed) {
		while (!kthread_should_stop()) {
			msleep(100);
		}
	}
	return 0;
}