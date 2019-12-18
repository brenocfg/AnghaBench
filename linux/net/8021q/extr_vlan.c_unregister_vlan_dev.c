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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_group {scalar_t__ nr_vlan_devs; } ;
struct vlan_info {struct vlan_group grp; } ;
struct vlan_dev_priv {int flags; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan_id; struct net_device* real_dev; } ;
struct net_device {int /*<<< orphan*/  vlan_info; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int VLAN_FLAG_GVRP ; 
 int VLAN_FLAG_MVRP ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 struct vlan_info* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vlan_group_set_device (struct vlan_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_gvrp_request_leave (struct net_device*) ; 
 int /*<<< orphan*/  vlan_gvrp_uninit_applicant (struct net_device*) ; 
 int /*<<< orphan*/  vlan_mvrp_request_leave (struct net_device*) ; 
 int /*<<< orphan*/  vlan_mvrp_uninit_applicant (struct net_device*) ; 
 int /*<<< orphan*/  vlan_vid_del (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void unregister_vlan_dev(struct net_device *dev, struct list_head *head)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	struct net_device *real_dev = vlan->real_dev;
	struct vlan_info *vlan_info;
	struct vlan_group *grp;
	u16 vlan_id = vlan->vlan_id;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(real_dev->vlan_info);
	BUG_ON(!vlan_info);

	grp = &vlan_info->grp;

	grp->nr_vlan_devs--;

	if (vlan->flags & VLAN_FLAG_MVRP)
		vlan_mvrp_request_leave(dev);
	if (vlan->flags & VLAN_FLAG_GVRP)
		vlan_gvrp_request_leave(dev);

	vlan_group_set_device(grp, vlan->vlan_proto, vlan_id, NULL);

	netdev_upper_dev_unlink(real_dev, dev);
	/* Because unregister_netdevice_queue() makes sure at least one rcu
	 * grace period is respected before device freeing,
	 * we dont need to call synchronize_net() here.
	 */
	unregister_netdevice_queue(dev, head);

	if (grp->nr_vlan_devs == 0) {
		vlan_mvrp_uninit_applicant(real_dev);
		vlan_gvrp_uninit_applicant(real_dev);
	}

	vlan_vid_del(real_dev, vlan->vlan_proto, vlan_id);

	/* Get rid of the vlan's reference to real_dev */
	dev_put(real_dev);
}