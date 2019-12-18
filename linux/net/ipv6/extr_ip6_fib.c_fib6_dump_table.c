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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct netlink_callback {scalar_t__* args; } ;
struct net {int dummy; } ;
struct fib6_walker {scalar_t__ skip; scalar_t__ skip_in_node; scalar_t__ count; TYPE_1__* root; TYPE_1__* node; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int fn_sernum; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; TYPE_1__ tb6_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWS_INIT ; 
 int fib6_walk (struct net*,struct fib6_walker*) ; 
 int fib6_walk_continue (struct fib6_walker*) ; 
 int /*<<< orphan*/  fib6_walker_unlink (struct net*,struct fib6_walker*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_dump_table(struct fib6_table *table, struct sk_buff *skb,
			   struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct fib6_walker *w;
	int res;

	w = (void *)cb->args[2];
	w->root = &table->tb6_root;

	if (cb->args[4] == 0) {
		w->count = 0;
		w->skip = 0;
		w->skip_in_node = 0;

		spin_lock_bh(&table->tb6_lock);
		res = fib6_walk(net, w);
		spin_unlock_bh(&table->tb6_lock);
		if (res > 0) {
			cb->args[4] = 1;
			cb->args[5] = w->root->fn_sernum;
		}
	} else {
		if (cb->args[5] != w->root->fn_sernum) {
			/* Begin at the root if the tree changed */
			cb->args[5] = w->root->fn_sernum;
			w->state = FWS_INIT;
			w->node = w->root;
			w->skip = w->count;
			w->skip_in_node = 0;
		} else
			w->skip = 0;

		spin_lock_bh(&table->tb6_lock);
		res = fib6_walk_continue(w);
		spin_unlock_bh(&table->tb6_lock);
		if (res <= 0) {
			fib6_walker_unlink(net, w);
			cb->args[4] = 0;
		}
	}

	return res;
}