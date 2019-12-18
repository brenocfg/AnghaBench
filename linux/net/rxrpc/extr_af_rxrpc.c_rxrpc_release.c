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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct socket*,struct sock*) ; 
 int rxrpc_release_sock (struct sock*) ; 

__attribute__((used)) static int rxrpc_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	_enter("%p{%p}", sock, sk);

	if (!sk)
		return 0;

	sock->sk = NULL;

	return rxrpc_release_sock(sk);
}