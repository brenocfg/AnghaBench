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
struct vxlan_rdst {int /*<<< orphan*/  remote_ifindex; int /*<<< orphan*/  remote_vni; int /*<<< orphan*/  remote_ip; } ;
struct vxlan_fdb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_port; } ;
struct vxlan_dev {int /*<<< orphan*/  hash_lock; TYPE_1__ cfg; int /*<<< orphan*/  net; struct vxlan_rdst default_dst; } ;
struct vxlan_config {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTF_SELF ; 
 int NUD_PERMANENT ; 
 int NUD_REACHABLE ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 int /*<<< orphan*/  __vxlan_fdb_delete (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_zeros_mac ; 
 int /*<<< orphan*/  first_remote_rtnl (struct vxlan_fdb*) ; 
 int /*<<< orphan*/  memcpy (struct vxlan_rdst*,struct vxlan_rdst*,int) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vxlan_dev_configure (int /*<<< orphan*/ ,struct net_device*,struct vxlan_config*,int,struct netlink_ext_ack*) ; 
 int vxlan_fdb_create (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vxlan_fdb**) ; 
 int /*<<< orphan*/  vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vxlan_nl2conf (struct nlattr**,struct nlattr**,struct net_device*,struct vxlan_config*,int) ; 

__attribute__((used)) static int vxlan_changelink(struct net_device *dev, struct nlattr *tb[],
			    struct nlattr *data[],
			    struct netlink_ext_ack *extack)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_rdst *dst = &vxlan->default_dst;
	struct vxlan_rdst old_dst;
	struct vxlan_config conf;
	struct vxlan_fdb *f = NULL;
	int err;

	err = vxlan_nl2conf(tb, data,
			    dev, &conf, true);
	if (err)
		return err;

	memcpy(&old_dst, dst, sizeof(struct vxlan_rdst));

	err = vxlan_dev_configure(vxlan->net, dev, &conf, true, extack);
	if (err)
		return err;

	/* handle default dst entry */
	if (!vxlan_addr_equal(&dst->remote_ip, &old_dst.remote_ip)) {
		spin_lock_bh(&vxlan->hash_lock);
		if (!vxlan_addr_any(&old_dst.remote_ip))
			__vxlan_fdb_delete(vxlan, all_zeros_mac,
					   old_dst.remote_ip,
					   vxlan->cfg.dst_port,
					   old_dst.remote_vni,
					   old_dst.remote_vni,
					   old_dst.remote_ifindex, 0);

		if (!vxlan_addr_any(&dst->remote_ip)) {
			err = vxlan_fdb_create(vxlan, all_zeros_mac,
					       &dst->remote_ip,
					       NUD_REACHABLE | NUD_PERMANENT,
					       vxlan->cfg.dst_port,
					       dst->remote_vni,
					       dst->remote_vni,
					       dst->remote_ifindex,
					       NTF_SELF, &f);
			if (err) {
				spin_unlock_bh(&vxlan->hash_lock);
				return err;
			}
			vxlan_fdb_notify(vxlan, f, first_remote_rtnl(f), RTM_NEWNEIGH);
		}
		spin_unlock_bh(&vxlan->hash_lock);
	}

	return 0;
}