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
struct net_device {int dummy; } ;
struct batadv_hard_iface {struct net_device* soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_IF_CLEANUP_KEEP ; 
 int EINVAL ; 
 int /*<<< orphan*/  batadv_hardif_disable_interface (struct batadv_hard_iface*,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 

__attribute__((used)) static int batadv_softif_slave_del(struct net_device *dev,
				   struct net_device *slave_dev)
{
	struct batadv_hard_iface *hard_iface;
	int ret = -EINVAL;

	hard_iface = batadv_hardif_get_by_netdev(slave_dev);

	if (!hard_iface || hard_iface->soft_iface != dev)
		goto out;

	batadv_hardif_disable_interface(hard_iface, BATADV_IF_CLEANUP_KEEP);
	ret = 0;

out:
	if (hard_iface)
		batadv_hardif_put(hard_iface);
	return ret;
}