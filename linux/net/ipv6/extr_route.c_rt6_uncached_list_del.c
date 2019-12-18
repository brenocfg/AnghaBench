#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uncached_list {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_uncached; TYPE_3__ dst; struct uncached_list* rt6i_uncached_list; } ;
struct TYPE_5__ {TYPE_1__* rt6_stats; } ;
struct net {TYPE_2__ ipv6; } ;
struct TYPE_4__ {int /*<<< orphan*/  fib_rt_uncache; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rt6_uncached_list_del(struct rt6_info *rt)
{
	if (!list_empty(&rt->rt6i_uncached)) {
		struct uncached_list *ul = rt->rt6i_uncached_list;
		struct net *net = dev_net(rt->dst.dev);

		spin_lock_bh(&ul->lock);
		list_del(&rt->rt6i_uncached);
		atomic_dec(&net->ipv6.rt6_stats->fib_rt_uncache);
		spin_unlock_bh(&ul->lock);
	}
}