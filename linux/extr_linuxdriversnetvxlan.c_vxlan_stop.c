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
struct vxlan_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_ip; } ;
struct vxlan_dev {int /*<<< orphan*/  age_timer; TYPE_1__ default_dst; int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 scalar_t__ vxlan_addr_multicast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_flush (struct vxlan_dev*,int) ; 
 int /*<<< orphan*/  vxlan_group_used (struct vxlan_net*,struct vxlan_dev*) ; 
 int vxlan_igmp_leave (struct vxlan_dev*) ; 
 int /*<<< orphan*/  vxlan_net_id ; 
 int /*<<< orphan*/  vxlan_sock_release (struct vxlan_dev*) ; 

__attribute__((used)) static int vxlan_stop(struct net_device *dev)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);
	int ret = 0;

	if (vxlan_addr_multicast(&vxlan->default_dst.remote_ip) &&
	    !vxlan_group_used(vn, vxlan))
		ret = vxlan_igmp_leave(vxlan);

	del_timer_sync(&vxlan->age_timer);

	vxlan_flush(vxlan, false);
	vxlan_sock_release(vxlan);

	return ret;
}