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
struct tipc_msg {int dummy; } ;
struct tipc_sock {int /*<<< orphan*/  sk; struct tipc_msg phdr; } ;
struct tipc_net {int /*<<< orphan*/  sk_rht; } ;
struct rhashtable_iter {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct tipc_sock* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct tipc_sock*) ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_prevnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_walk_enter (int /*<<< orphan*/ *,struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (struct rhashtable_iter*) ; 
 struct tipc_sock* rhashtable_walk_next (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_start (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_stop (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_id ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 

void tipc_sk_reinit(struct net *net)
{
	struct tipc_net *tn = net_generic(net, tipc_net_id);
	struct rhashtable_iter iter;
	struct tipc_sock *tsk;
	struct tipc_msg *msg;

	rhashtable_walk_enter(&tn->sk_rht, &iter);

	do {
		rhashtable_walk_start(&iter);

		while ((tsk = rhashtable_walk_next(&iter)) && !IS_ERR(tsk)) {
			sock_hold(&tsk->sk);
			rhashtable_walk_stop(&iter);
			lock_sock(&tsk->sk);
			msg = &tsk->phdr;
			msg_set_prevnode(msg, tipc_own_addr(net));
			msg_set_orignode(msg, tipc_own_addr(net));
			release_sock(&tsk->sk);
			rhashtable_walk_start(&iter);
			sock_put(&tsk->sk);
		}

		rhashtable_walk_stop(&iter);
	} while (tsk == ERR_PTR(-EAGAIN));

	rhashtable_walk_exit(&iter);
}