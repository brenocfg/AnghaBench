#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; int sk_max_ack_backlog; scalar_t__ sk_ack_backlog; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ BT_BOUND ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int) ; 
 scalar_t__ BT_LISTEN ; 
 int EADDRINUSE ; 
 int EBADFD ; 
 int EINVAL ; 
 scalar_t__ SOCK_SEQPACKET ; 
 scalar_t__ __sco_get_sock_listen_by_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 TYPE_2__* sco_pi (struct sock*) ; 
 TYPE_1__ sco_sk_list ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sco_sock_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	bdaddr_t *src = &sco_pi(sk)->src;
	int err = 0;

	BT_DBG("sk %p backlog %d", sk, backlog);

	lock_sock(sk);

	if (sk->sk_state != BT_BOUND) {
		err = -EBADFD;
		goto done;
	}

	if (sk->sk_type != SOCK_SEQPACKET) {
		err = -EINVAL;
		goto done;
	}

	write_lock(&sco_sk_list.lock);

	if (__sco_get_sock_listen_by_addr(src)) {
		err = -EADDRINUSE;
		goto unlock;
	}

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;

	sk->sk_state = BT_LISTEN;

unlock:
	write_unlock(&sco_sk_list.lock);

done:
	release_sock(sk);
	return err;
}