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
struct sock {scalar_t__ sk_state; } ;
struct sco_pinfo {int /*<<< orphan*/  setting; TYPE_1__* conn; } ;
struct msghdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  hcon; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECT2 ; 
 int /*<<< orphan*/  BT_SK_DEFER_SETUP ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int bt_sock_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sco_conn_defer_accept (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sco_pinfo* sco_pi (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sco_sock_recvmsg(struct socket *sock, struct msghdr *msg,
			    size_t len, int flags)
{
	struct sock *sk = sock->sk;
	struct sco_pinfo *pi = sco_pi(sk);

	lock_sock(sk);

	if (sk->sk_state == BT_CONNECT2 &&
	    test_bit(BT_SK_DEFER_SETUP, &bt_sk(sk)->flags)) {
		sco_conn_defer_accept(pi->conn->hcon, pi->setting);
		sk->sk_state = BT_CONFIG;

		release_sock(sk);
		return 0;
	}

	release_sock(sk);

	return bt_sock_recvmsg(sock, msg, len, flags);
}