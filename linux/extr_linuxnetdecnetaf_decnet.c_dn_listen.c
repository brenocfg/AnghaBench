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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_max_ack_backlog; scalar_t__ sk_ack_backlog; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DN_O ; 
 TYPE_1__* DN_SK (struct sock*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  dn_rehash_sock (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	int err = -EINVAL;

	lock_sock(sk);

	if (sock_flag(sk, SOCK_ZAPPED))
		goto out;

	if ((DN_SK(sk)->state != DN_O) || (sk->sk_state == TCP_LISTEN))
		goto out;

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog     = 0;
	sk->sk_state           = TCP_LISTEN;
	err                 = 0;
	dn_rehash_sock(sk);

out:
	release_sock(sk);

	return err;
}