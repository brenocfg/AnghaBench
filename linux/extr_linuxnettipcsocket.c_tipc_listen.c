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
 int /*<<< orphan*/  TIPC_LISTEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int tipc_set_sk_state (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_listen(struct socket *sock, int len)
{
	struct sock *sk = sock->sk;
	int res;

	lock_sock(sk);
	res = tipc_set_sk_state(sk, TIPC_LISTEN);
	release_sock(sk);

	return res;
}