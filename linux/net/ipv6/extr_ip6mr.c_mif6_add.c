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
struct vif_device {int const flags; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct mr_table {int mroute_reg_vif_num; int maxvif; int /*<<< orphan*/  id; struct vif_device* vif_table; } ;
struct mif6ctl {int mif6c_mifi; int mif6c_flags; int /*<<< orphan*/  vifc_threshold; int /*<<< orphan*/  vifc_rate_limit; int /*<<< orphan*/  mif6c_pifi; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_forwarding; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  FIB_EVENT_VIF_ADD ; 
#define  MIFF_REGISTER 128 
 int /*<<< orphan*/  NETCONFA_MC_FORWARDING ; 
 int /*<<< orphan*/  RTM_NEWNETCONF ; 
 int VIFF_STATIC ; 
 scalar_t__ VIF_EXISTS (struct mr_table*,int) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  call_ip6mr_vif_entry_notifiers (struct net*,int /*<<< orphan*/ ,struct vif_device*,int,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  inet6_netconf_notify_devconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct net_device* ip6mr_reg_vif (struct net*,struct mr_table*) ; 
 int /*<<< orphan*/  mrt_lock ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  vif_device_init (struct vif_device*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mif6_add(struct net *net, struct mr_table *mrt,
		    struct mif6ctl *vifc, int mrtsock)
{
	int vifi = vifc->mif6c_mifi;
	struct vif_device *v = &mrt->vif_table[vifi];
	struct net_device *dev;
	struct inet6_dev *in6_dev;
	int err;

	/* Is vif busy ? */
	if (VIF_EXISTS(mrt, vifi))
		return -EADDRINUSE;

	switch (vifc->mif6c_flags) {
#ifdef CONFIG_IPV6_PIMSM_V2
	case MIFF_REGISTER:
		/*
		 * Special Purpose VIF in PIM
		 * All the packets will be sent to the daemon
		 */
		if (mrt->mroute_reg_vif_num >= 0)
			return -EADDRINUSE;
		dev = ip6mr_reg_vif(net, mrt);
		if (!dev)
			return -ENOBUFS;
		err = dev_set_allmulti(dev, 1);
		if (err) {
			unregister_netdevice(dev);
			dev_put(dev);
			return err;
		}
		break;
#endif
	case 0:
		dev = dev_get_by_index(net, vifc->mif6c_pifi);
		if (!dev)
			return -EADDRNOTAVAIL;
		err = dev_set_allmulti(dev, 1);
		if (err) {
			dev_put(dev);
			return err;
		}
		break;
	default:
		return -EINVAL;
	}

	in6_dev = __in6_dev_get(dev);
	if (in6_dev) {
		in6_dev->cnf.mc_forwarding++;
		inet6_netconf_notify_devconf(dev_net(dev), RTM_NEWNETCONF,
					     NETCONFA_MC_FORWARDING,
					     dev->ifindex, &in6_dev->cnf);
	}

	/* Fill in the VIF structures */
	vif_device_init(v, dev, vifc->vifc_rate_limit, vifc->vifc_threshold,
			vifc->mif6c_flags | (!mrtsock ? VIFF_STATIC : 0),
			MIFF_REGISTER);

	/* And finish update writing critical data */
	write_lock_bh(&mrt_lock);
	v->dev = dev;
#ifdef CONFIG_IPV6_PIMSM_V2
	if (v->flags & MIFF_REGISTER)
		mrt->mroute_reg_vif_num = vifi;
#endif
	if (vifi + 1 > mrt->maxvif)
		mrt->maxvif = vifi + 1;
	write_unlock_bh(&mrt_lock);
	call_ip6mr_vif_entry_notifiers(net, FIB_EVENT_VIF_ADD,
				       v, vifi, mrt->id);
	return 0;
}