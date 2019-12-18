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
struct work_struct {int dummy; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; int /*<<< orphan*/ * sk_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (struct work_struct*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void rds_tcp_listen_stop(struct socket *sock, struct work_struct *acceptor)
{
	struct sock *sk;

	if (!sock)
		return;

	sk = sock->sk;

	/* serialize with and prevent further callbacks */
	lock_sock(sk);
	write_lock_bh(&sk->sk_callback_lock);
	if (sk->sk_user_data) {
		sk->sk_data_ready = sk->sk_user_data;
		sk->sk_user_data = NULL;
	}
	write_unlock_bh(&sk->sk_callback_lock);
	release_sock(sk);

	/* wait for accepts to stop and close the socket */
	flush_workqueue(rds_wq);
	flush_work(acceptor);
	sock_release(sock);
}