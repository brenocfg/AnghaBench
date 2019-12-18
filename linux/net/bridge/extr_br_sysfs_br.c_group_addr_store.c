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
typedef  int u8 ;
struct net_bridge {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  group_addr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_GROUP_ADDR_SET ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  br_opt_toggle (struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_recalculate_fwd_mask (struct net_bridge*) ; 
 TYPE_1__* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  is_link_local_ether_addr (int*) ; 
 int /*<<< orphan*/  mac_pton (char const*,int*) ; 
 int /*<<< orphan*/  netdev_state_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t restart_syscall () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct net_bridge* to_bridge (struct device*) ; 

__attribute__((used)) static ssize_t group_addr_store(struct device *d,
				struct device_attribute *attr,
				const char *buf, size_t len)
{
	struct net_bridge *br = to_bridge(d);
	u8 new_addr[6];

	if (!ns_capable(dev_net(br->dev)->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	if (!mac_pton(buf, new_addr))
		return -EINVAL;

	if (!is_link_local_ether_addr(new_addr))
		return -EINVAL;

	if (new_addr[5] == 1 ||		/* 802.3x Pause address */
	    new_addr[5] == 2 ||		/* 802.3ad Slow protocols */
	    new_addr[5] == 3)		/* 802.1X PAE address */
		return -EINVAL;

	if (!rtnl_trylock())
		return restart_syscall();

	spin_lock_bh(&br->lock);
	ether_addr_copy(br->group_addr, new_addr);
	spin_unlock_bh(&br->lock);

	br_opt_toggle(br, BROPT_GROUP_ADDR_SET, true);
	br_recalculate_fwd_mask(br);
	netdev_state_change(br->dev);

	rtnl_unlock();

	return len;
}