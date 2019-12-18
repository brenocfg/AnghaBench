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
struct sock {int dummy; } ;
struct netlink_sock {int /*<<< orphan*/  (* netlink_unbind ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static void netlink_undo_bind(int group, long unsigned int groups,
			      struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	int undo;

	if (!nlk->netlink_unbind)
		return;

	for (undo = 0; undo < group; undo++)
		if (test_bit(undo, &groups))
			nlk->netlink_unbind(sock_net(sk), undo + 1);
}