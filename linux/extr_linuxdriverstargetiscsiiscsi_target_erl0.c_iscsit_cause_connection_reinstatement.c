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
struct iscsi_conn {int /*<<< orphan*/  conn_post_wait_comp; int /*<<< orphan*/  conn_wait_comp; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  sleep_on_conn_wait_comp; int /*<<< orphan*/  connection_reinstatement; scalar_t__ rx_thread; scalar_t__ rx_thread_active; scalar_t__ tx_thread; scalar_t__ tx_thread_active; int /*<<< orphan*/  transport_failed; int /*<<< orphan*/  connection_exit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void iscsit_cause_connection_reinstatement(struct iscsi_conn *conn, int sleep)
{
	spin_lock_bh(&conn->state_lock);
	if (atomic_read(&conn->connection_exit)) {
		spin_unlock_bh(&conn->state_lock);
		return;
	}

	if (atomic_read(&conn->transport_failed)) {
		spin_unlock_bh(&conn->state_lock);
		return;
	}

	if (atomic_read(&conn->connection_reinstatement)) {
		spin_unlock_bh(&conn->state_lock);
		return;
	}

	if (conn->tx_thread && conn->tx_thread_active)
		send_sig(SIGINT, conn->tx_thread, 1);
	if (conn->rx_thread && conn->rx_thread_active)
		send_sig(SIGINT, conn->rx_thread, 1);

	atomic_set(&conn->connection_reinstatement, 1);
	if (!sleep) {
		spin_unlock_bh(&conn->state_lock);
		return;
	}

	atomic_set(&conn->sleep_on_conn_wait_comp, 1);
	spin_unlock_bh(&conn->state_lock);

	wait_for_completion(&conn->conn_wait_comp);
	complete(&conn->conn_post_wait_comp);
}