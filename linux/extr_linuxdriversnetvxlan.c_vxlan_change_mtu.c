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
struct vxlan_rdst {int /*<<< orphan*/  remote_ifindex; } ;
struct TYPE_2__ {int flags; } ;
struct vxlan_dev {TYPE_1__ cfg; int /*<<< orphan*/  net; struct vxlan_rdst default_dst; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int VXLAN6_HEADROOM ; 
 int VXLAN_F_IPV6 ; 
 int VXLAN_HEADROOM ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int vxlan_change_mtu(struct net_device *dev, int new_mtu)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_rdst *dst = &vxlan->default_dst;
	struct net_device *lowerdev = __dev_get_by_index(vxlan->net,
							 dst->remote_ifindex);
	bool use_ipv6 = !!(vxlan->cfg.flags & VXLAN_F_IPV6);

	/* This check is different than dev->max_mtu, because it looks at
	 * the lowerdev->mtu, rather than the static dev->max_mtu
	 */
	if (lowerdev) {
		int max_mtu = lowerdev->mtu -
			      (use_ipv6 ? VXLAN6_HEADROOM : VXLAN_HEADROOM);
		if (new_mtu > max_mtu)
			return -EINVAL;
	}

	dev->mtu = new_mtu;
	return 0;
}