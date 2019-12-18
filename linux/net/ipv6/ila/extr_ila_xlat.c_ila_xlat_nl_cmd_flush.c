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
struct sk_buff {int dummy; } ;
struct rhashtable_iter {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_1__ xlat; } ;
struct ila_map {int /*<<< orphan*/  node; } ;
struct genl_info {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct ila_map*) ; 
 int PTR_ERR (struct ila_map*) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  ila_free_node (struct ila_map*) ; 
 int /*<<< orphan*/  ila_net_id ; 
 int /*<<< orphan*/ * lock_from_ila_map (struct ila_net*,struct ila_map*) ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_walk_enter (int /*<<< orphan*/ *,struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (struct rhashtable_iter*) ; 
 struct ila_map* rhashtable_walk_next (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_start (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_stop (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rht_params ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ila_xlat_nl_cmd_flush(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct ila_net *ilan = net_generic(net, ila_net_id);
	struct rhashtable_iter iter;
	struct ila_map *ila;
	spinlock_t *lock;
	int ret = 0;

	rhashtable_walk_enter(&ilan->xlat.rhash_table, &iter);
	rhashtable_walk_start(&iter);

	for (;;) {
		ila = rhashtable_walk_next(&iter);

		if (IS_ERR(ila)) {
			if (PTR_ERR(ila) == -EAGAIN)
				continue;
			ret = PTR_ERR(ila);
			goto done;
		} else if (!ila) {
			break;
		}

		lock = lock_from_ila_map(ilan, ila);

		spin_lock(lock);

		ret = rhashtable_remove_fast(&ilan->xlat.rhash_table,
					     &ila->node, rht_params);
		if (!ret)
			ila_free_node(ila);

		spin_unlock(lock);

		if (ret)
			break;
	}

done:
	rhashtable_walk_stop(&iter);
	rhashtable_walk_exit(&iter);
	return ret;
}