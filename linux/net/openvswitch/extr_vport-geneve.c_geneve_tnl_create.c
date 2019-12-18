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
struct vport_parms {int /*<<< orphan*/  name; struct nlattr* options; int /*<<< orphan*/  dp; } ;
struct vport {int flags; } ;
struct nlattr {int dummy; } ;
struct net_device {int flags; } ;
struct net {int dummy; } ;
struct geneve_port {int /*<<< orphan*/  dst_port; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vport* ERR_CAST (struct vport*) ; 
 struct vport* ERR_PTR (int) ; 
 int IFF_UP ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  NET_NAME_USER ; 
 int /*<<< orphan*/  OVS_TUNNEL_ATTR_DST_PORT ; 
 int dev_change_flags (struct vport*,int,int /*<<< orphan*/ *) ; 
 struct vport* geneve_dev_create_fb (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct geneve_port* geneve_vport (struct vport*) ; 
 struct nlattr* nla_find_nested (struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct net* ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_geneve_vport_ops ; 
 struct vport* ovs_vport_alloc (int,int /*<<< orphan*/ *,struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_free (struct vport*) ; 
 int /*<<< orphan*/  rtnl_delete_link (struct vport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static struct vport *geneve_tnl_create(const struct vport_parms *parms)
{
	struct net *net = ovs_dp_get_net(parms->dp);
	struct nlattr *options = parms->options;
	struct geneve_port *geneve_port;
	struct net_device *dev;
	struct vport *vport;
	struct nlattr *a;
	u16 dst_port;
	int err;

	if (!options) {
		err = -EINVAL;
		goto error;
	}

	a = nla_find_nested(options, OVS_TUNNEL_ATTR_DST_PORT);
	if (a && nla_len(a) == sizeof(u16)) {
		dst_port = nla_get_u16(a);
	} else {
		/* Require destination port from userspace. */
		err = -EINVAL;
		goto error;
	}

	vport = ovs_vport_alloc(sizeof(struct geneve_port),
				&ovs_geneve_vport_ops, parms);
	if (IS_ERR(vport))
		return vport;

	geneve_port = geneve_vport(vport);
	geneve_port->dst_port = dst_port;

	rtnl_lock();
	dev = geneve_dev_create_fb(net, parms->name, NET_NAME_USER, dst_port);
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