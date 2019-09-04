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
struct tipc_conn {int /*<<< orphan*/  rwork; TYPE_1__* server; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; struct tipc_conn* sk_user_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcv_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_get (struct tipc_conn*) ; 
 int /*<<< orphan*/  conn_put (struct tipc_conn*) ; 
 scalar_t__ connected (struct tipc_conn*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tipc_conn_data_ready(struct sock *sk)
{
	struct tipc_conn *con;

	read_lock_bh(&sk->sk_callback_lock);
	con = sk->sk_user_data;
	if (connected(con)) {
		conn_get(con);
		if (!queue_work(con->server->rcv_wq, &con->rwork))
			conn_put(con);
	}
	read_unlock_bh(&sk->sk_callback_lock);
}