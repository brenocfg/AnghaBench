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
struct vxlan_net {int /*<<< orphan*/  vxlan_list; } ;
struct vxlan_fdb {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  remote_ifindex; int /*<<< orphan*/  remote_vni; int /*<<< orphan*/  remote_ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst_port; } ;
struct vxlan_dev {int /*<<< orphan*/  next; TYPE_2__ default_dst; TYPE_1__ cfg; } ;
struct vxlan_config {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTF_SELF ; 
 int NUD_PERMANENT ; 
 int NUD_REACHABLE ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 int /*<<< orphan*/  all_zeros_mac ; 
 int /*<<< orphan*/  first_remote_rtnl (struct vxlan_fdb*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int rtnl_configure_link (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  vxlan_addr_any (int /*<<< orphan*/ *) ; 
 int vxlan_dev_configure (struct net*,struct net_device*,struct vxlan_config*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  vxlan_ethtool_ops ; 
 int vxlan_fdb_create (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vxlan_fdb**) ; 
 int /*<<< orphan*/  vxlan_fdb_destroy (struct vxlan_dev*,struct vxlan_fdb*,int) ; 
 int /*<<< orphan*/  vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_net_id ; 

__attribute__((used)) static int __vxlan_dev_create(struct net *net, struct net_device *dev,
			      struct vxlan_config *conf,
			      struct netlink_ext_ack *extack)
{
	struct vxlan_net *vn = net_generic(net, vxlan_net_id);
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_fdb *f = NULL;
	int err;

	err = vxlan_dev_configure(net, dev, conf, false, extack);
	if (err)
		return err;

	dev->ethtool_ops = &vxlan_ethtool_ops;

	/* create an fdb entry for a valid default destination */
	if (!vxlan_addr_any(&vxlan->default_dst.remote_ip)) {
		err = vxlan_fdb_create(vxlan, all_zeros_mac,
				       &vxlan->default_dst.remote_ip,
				       NUD_REACHABLE | NUD_PERMANENT,
				       vxlan->cfg.dst_port,
				       vxlan->default_dst.remote_vni,
				       vxlan->default_dst.remote_vni,
				       vxlan->default_dst.remote_ifindex,
				       NTF_SELF, &f);
		if (err)
			return err;
	}

	err = register_netdevice(dev);
	if (err)
		goto errout;

	err = rtnl_configure_link(dev, NULL);
	if (err) {
		unregister_netdevice(dev);
		goto errout;
	}

	/* notify default fdb entry */
	if (f)
		vxlan_fdb_notify(vxlan, f, first_remote_rtnl(f), RTM_NEWNEIGH);

	list_add(&vxlan->next, &vn->vxlan_list);
	return 0;
errout:
	if (f)
		vxlan_fdb_destroy(vxlan, f, false);
	return err;
}