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
struct sock {int /*<<< orphan*/  sk_drops; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_err; } ;
struct netlink_sock {int flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int NETLINK_F_RECV_NO_ENOBUFS ; 
 int /*<<< orphan*/  NETLINK_S_CONGESTED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netlink_overrun(struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (!(nlk->flags & NETLINK_F_RECV_NO_ENOBUFS)) {
		if (!test_and_set_bit(NETLINK_S_CONGESTED,
				      &nlk_sk(sk)->state)) {
			sk->sk_err = ENOBUFS;
			sk->sk_error_report(sk);
		}
	}
	atomic_inc(&sk->sk_drops);
}