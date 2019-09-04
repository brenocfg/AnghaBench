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
struct socket {int /*<<< orphan*/  state; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; TYPE_1__* sk_prot; } ;
struct TYPE_2__ {struct sock* (* accept ) (struct sock*,int,int*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_graft (struct sock*,struct socket*) ; 
 struct sock* stub1 (struct sock*,int,int*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pn_socket_accept(struct socket *sock, struct socket *newsock,
			    int flags, bool kern)
{
	struct sock *sk = sock->sk;
	struct sock *newsk;
	int err;

	if (unlikely(sk->sk_state != TCP_LISTEN))
		return -EINVAL;

	newsk = sk->sk_prot->accept(sk, flags, &err, kern);
	if (!newsk)
		return err;

	lock_sock(newsk);
	sock_graft(newsk, newsock);
	newsock->state = SS_CONNECTED;
	release_sock(newsk);
	return 0;
}