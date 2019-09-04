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
struct tipc_sock {struct tipc_group* group; int /*<<< orphan*/  sk; } ;
struct tipc_name_seq {int dummy; } ;
struct tipc_group {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct net* sock_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_group_delete (struct net*,struct tipc_group*) ; 
 int /*<<< orphan*/  tipc_group_self (struct tipc_group*,struct tipc_name_seq*,int*) ; 
 int /*<<< orphan*/  tipc_sk_withdraw (struct tipc_sock*,int,struct tipc_name_seq*) ; 

__attribute__((used)) static int tipc_sk_leave(struct tipc_sock *tsk)
{
	struct net *net = sock_net(&tsk->sk);
	struct tipc_group *grp = tsk->group;
	struct tipc_name_seq seq;
	int scope;

	if (!grp)
		return -EINVAL;
	tipc_group_self(grp, &seq, &scope);
	tipc_group_delete(net, grp);
	tsk->group = NULL;
	tipc_sk_withdraw(tsk, scope, &seq);
	return 0;
}