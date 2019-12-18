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

/* Variables and functions */
 size_t BATADV_ATTR_MESH_IFINDEX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_softif_is_valid (struct net_device*) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *
batadv_get_softif_from_info(struct net *net, struct genl_info *info)
{
	struct net_device *soft_iface;
	int ifindex;

	if (!info->attrs[BATADV_ATTR_MESH_IFINDEX])
		return ERR_PTR(-EINVAL);

	ifindex = nla_get_u32(info->attrs[BATADV_ATTR_MESH_IFINDEX]);

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface)
		return ERR_PTR(-ENODEV);

	if (!batadv_softif_is_valid(soft_iface))
		goto err_put_softif;

	return soft_iface;

err_put_softif:
	dev_put(soft_iface);

	return ERR_PTR(-EINVAL);
}