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
struct iscsi_conn {int /*<<< orphan*/  conn_logout_comp; int /*<<< orphan*/  conn_logout_remove; int /*<<< orphan*/  tx_thread_active; TYPE_1__* conn_transport; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdma_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_cause_connection_reinstatement (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  iscsit_dec_conn_usage_count (struct iscsi_conn*) ; 

__attribute__((used)) static void iscsit_logout_post_handler_samecid(
	struct iscsi_conn *conn)
{
	int sleep = 1;

	if (!conn->conn_transport->rdma_shutdown) {
		sleep = cmpxchg(&conn->tx_thread_active, true, false);
		if (!sleep)
			return;
	}

	atomic_set(&conn->conn_logout_remove, 0);
	complete(&conn->conn_logout_comp);

	iscsit_cause_connection_reinstatement(conn, sleep);
	iscsit_dec_conn_usage_count(conn);
}