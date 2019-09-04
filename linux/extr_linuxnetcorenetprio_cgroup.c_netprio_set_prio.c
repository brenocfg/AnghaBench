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
typedef  scalar_t__ u32 ;
struct netprio_map {int priomap_len; scalar_t__* priomap; } ;
struct net_device {int /*<<< orphan*/  priomap; } ;
struct cgroup_subsys_state {TYPE_1__* cgroup; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int extend_netdev_table (struct net_device*,int) ; 
 struct netprio_map* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netprio_set_prio(struct cgroup_subsys_state *css,
			    struct net_device *dev, u32 prio)
{
	struct netprio_map *map;
	int id = css->cgroup->id;
	int ret;

	/* avoid extending priomap for zero writes */
	map = rtnl_dereference(dev->priomap);
	if (!prio && (!map || map->priomap_len <= id))
		return 0;

	ret = extend_netdev_table(dev, id);
	if (ret)
		return ret;

	map = rtnl_dereference(dev->priomap);
	map->priomap[id] = prio;
	return 0;
}