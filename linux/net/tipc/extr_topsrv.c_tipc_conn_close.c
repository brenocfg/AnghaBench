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
struct tipc_conn {TYPE_1__* sock; int /*<<< orphan*/  flags; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONNECTED ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  conn_put (struct tipc_conn*) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_conn_delete_sub (struct tipc_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tipc_conn_close(struct tipc_conn *con)
{
	struct sock *sk = con->sock->sk;
	bool disconnect = false;

	write_lock_bh(&sk->sk_callback_lock);
	disconnect = test_and_clear_bit(CF_CONNECTED, &con->flags);

	if (disconnect) {
		sk->sk_user_data = NULL;
		tipc_conn_delete_sub(con, NULL);
	}
	write_unlock_bh(&sk->sk_callback_lock);

	/* Handle concurrent calls from sending and receiving threads */
	if (!disconnect)
		return;

	/* Don't flush pending works, -just let them expire */
	kernel_sock_shutdown(con->sock, SHUT_RDWR);

	conn_put(con);
}