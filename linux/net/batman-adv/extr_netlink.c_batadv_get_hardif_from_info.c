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
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct batadv_priv {scalar_t__ soft_iface; } ;
struct batadv_hard_iface {scalar_t__ soft_iface; } ;

/* Variables and functions */
 size_t BATADV_ATTR_HARD_IFINDEX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct batadv_hard_iface* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct net_device* dev_get_by_index (struct net*,unsigned int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 unsigned int nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct batadv_hard_iface *
batadv_get_hardif_from_info(struct batadv_priv *bat_priv, struct net *net,
			    struct genl_info *info)
{
	struct batadv_hard_iface *hard_iface;
	struct net_device *hard_dev;
	unsigned int hardif_index;

	if (!info->attrs[BATADV_ATTR_HARD_IFINDEX])
		return ERR_PTR(-EINVAL);

	hardif_index = nla_get_u32(info->attrs[BATADV_ATTR_HARD_IFINDEX]);

	hard_dev = dev_get_by_index(net, hardif_index);
	if (!hard_dev)
		return ERR_PTR(-ENODEV);

	hard_iface = batadv_hardif_get_by_netdev(hard_dev);
	if (!hard_iface)
		goto err_put_harddev;

	if (hard_iface->soft_iface != bat_priv->soft_iface)
		goto err_put_hardif;

	/* hard_dev is referenced by hard_iface and not needed here */
	dev_put(hard_dev);

	return hard_iface;

err_put_hardif:
	batadv_hardif_put(hard_iface);
err_put_harddev:
	dev_put(hard_dev);

	return ERR_PTR(-EINVAL);
}