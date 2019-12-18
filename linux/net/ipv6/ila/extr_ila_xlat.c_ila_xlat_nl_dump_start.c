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
struct netlink_callback {long* args; TYPE_1__* skb; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_2__ xlat; } ;
struct ila_dump_iter {scalar_t__ skip; int /*<<< orphan*/  rhiter; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ila_net_id ; 
 struct ila_dump_iter* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_walk_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int ila_xlat_nl_dump_start(struct netlink_callback *cb)
{
	struct net *net = sock_net(cb->skb->sk);
	struct ila_net *ilan = net_generic(net, ila_net_id);
	struct ila_dump_iter *iter;

	iter = kmalloc(sizeof(*iter), GFP_KERNEL);
	if (!iter)
		return -ENOMEM;

	rhashtable_walk_enter(&ilan->xlat.rhash_table, &iter->rhiter);

	iter->skip = 0;
	cb->args[0] = (long)iter;

	return 0;
}