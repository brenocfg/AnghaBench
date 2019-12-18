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
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int /*<<< orphan*/  bt_sock_unlink (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  l2cap_sk_list ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int l2cap_sock_shutdown (struct socket*,int) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 

__attribute__((used)) static int l2cap_sock_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	int err;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (!sk)
		return 0;

	bt_sock_unlink(&l2cap_sk_list, sk);

	err = l2cap_sock_shutdown(sock, 2);

	sock_orphan(sk);
	l2cap_sock_kill(sk);
	return err;
}