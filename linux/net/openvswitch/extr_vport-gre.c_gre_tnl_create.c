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
struct vport_parms {int /*<<< orphan*/  name; int /*<<< orphan*/  dp; } ;
struct vport {int flags; } ;
struct net_device {int flags; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct vport* ERR_CAST (struct vport*) ; 
 struct vport* ERR_PTR (int) ; 
 int IFF_UP ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  NET_NAME_USER ; 
 int dev_change_flags (struct vport*,int,int /*<<< orphan*/ *) ; 
 struct vport* gretap_fb_dev_create (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_gre_vport_ops ; 
 struct vport* ovs_vport_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_free (struct vport*) ; 
 int /*<<< orphan*/  rtnl_delete_link (struct vport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static struct vport *gre_tnl_create(const struct vport_parms *parms)
{
	struct net *net = ovs_dp_get_net(parms->dp);
	struct net_device *dev;
	struct vport *vport;
	int err;

	vport = ovs_vport_alloc(0, &ovs_gre_vport_ops, parms);
	if (IS_ERR(vport))
		return vport;

	rtnl_lock();
	dev = gretap_fb_dev_create(net, parms->name, NET_NAME_USER);
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
		return ERR_PTR(err);
	}

	rtnl_unlock();
	return vport;
}