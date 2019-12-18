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
struct vxlan_config {int no_share; int flags; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  mtu; } ;
struct vport_parms {int /*<<< orphan*/  name; struct nlattr* options; int /*<<< orphan*/  dp; } ;
struct vport {int flags; } ;
struct nlattr {int dummy; } ;
struct net_device {int flags; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vport* ERR_CAST (struct vport*) ; 
 struct vport* ERR_PTR (int) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IP_MAX_MTU ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  NET_NAME_USER ; 
 int /*<<< orphan*/  OVS_TUNNEL_ATTR_DST_PORT ; 
 int /*<<< orphan*/  OVS_TUNNEL_ATTR_EXTENSION ; 
 int VXLAN_F_COLLECT_METADATA ; 
 int VXLAN_F_UDP_ZERO_CSUM6_RX ; 
 int dev_change_flags (struct vport*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct nlattr* nla_find_nested (struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct net* ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 struct vport* ovs_vport_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_free (struct vport*) ; 
 int /*<<< orphan*/  ovs_vxlan_netdev_vport_ops ; 
 int /*<<< orphan*/  rtnl_delete_link (struct vport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int vxlan_configure_exts (struct vport*,struct nlattr*,struct vxlan_config*) ; 
 struct vport* vxlan_dev_create (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vxlan_config*) ; 

__attribute__((used)) static struct vport *vxlan_tnl_create(const struct vport_parms *parms)
{
	struct net *net = ovs_dp_get_net(parms->dp);
	struct nlattr *options = parms->options;
	struct net_device *dev;
	struct vport *vport;
	struct nlattr *a;
	int err;
	struct vxlan_config conf = {
		.no_share = true,
		.flags = VXLAN_F_COLLECT_METADATA | VXLAN_F_UDP_ZERO_CSUM6_RX,
		/* Don't restrict the packets that can be sent by MTU */
		.mtu = IP_MAX_MTU,
	};

	if (!options) {
		err = -EINVAL;
		goto error;
	}

	a = nla_find_nested(options, OVS_TUNNEL_ATTR_DST_PORT);
	if (a && nla_len(a) == sizeof(u16)) {
		conf.dst_port = htons(nla_get_u16(a));
	} else {
		/* Require destination port from userspace. */
		err = -EINVAL;
		goto error;
	}

	vport = ovs_vport_alloc(0, &ovs_vxlan_netdev_vport_ops, parms);
	if (IS_ERR(vport))
		return vport;

	a = nla_find_nested(options, OVS_TUNNEL_ATTR_EXTENSION);
	if (a) {
		err = vxlan_configure_exts(vport, a, &conf);
		if (err) {
			ovs_vport_free(vport);
			goto error;
		}
	}

	rtnl_lock();
	dev = vxlan_dev_create(net, parms->name, NET_NAME_USER, &conf);
	if (IS_ERR(dev)) {
		rtnl_unlock();
		ovs_vport_free(vport);
		return ERR_CAST(dev);
	}

	err = dev_change_flags(dev, dev->flags | IFF_UP, NULL);
	if (err < 0) {
		rtnl_delete_link(dev);
		rtnl_unlock();
		ovs_vport_free(vport);
		goto error;
	}

	rtnl_unlock();
	return vport;
error:
	return ERR_PTR(err);
}