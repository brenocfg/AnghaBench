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
struct vif_device {int flags; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct mr_table {int maxvif; int mroute_reg_vif_num; int /*<<< orphan*/  id; int /*<<< orphan*/  net; struct vif_device* vif_table; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_forwarding; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  FIB_EVENT_VIF_DEL ; 
 int MIFF_REGISTER ; 
 int /*<<< orphan*/  NETCONFA_MC_FORWARDING ; 
 int /*<<< orphan*/  RTM_NEWNETCONF ; 
 scalar_t__ VIF_EXISTS (struct mr_table*,int) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  call_ip6mr_vif_entry_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vif_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  inet6_netconf_notify_devconf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mrt_lock ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mif6_delete(struct mr_table *mrt, int vifi, int notify,
		       struct list_head *head)
{
	struct vif_device *v;
	struct net_device *dev;
	struct inet6_dev *in6_dev;

	if (vifi < 0 || vifi >= mrt->maxvif)
		return -EADDRNOTAVAIL;

	v = &mrt->vif_table[vifi];

	if (VIF_EXISTS(mrt, vifi))
		call_ip6mr_vif_entry_notifiers(read_pnet(&mrt->net),
					       FIB_EVENT_VIF_DEL, v, vifi,
					       mrt->id);

	write_lock_bh(&mrt_lock);
	dev = v->dev;
	v->dev = NULL;

	if (!dev) {
		write_unlock_bh(&mrt_lock);
		return -EADDRNOTAVAIL;
	}

#ifdef CONFIG_IPV6_PIMSM_V2
	if (vifi == mrt->mroute_reg_vif_num)
		mrt->mroute_reg_vif_num = -1;
#endif

	if (vifi + 1 == mrt->maxvif) {
		int tmp;
		for (tmp = vifi - 1; tmp >= 0; tmp--) {
			if (VIF_EXISTS(mrt, tmp))
				break;
		}
		mrt->maxvif = tmp + 1;
	}

	write_unlock_bh(&mrt_lock);

	dev_set_allmulti(dev, -1);

	in6_dev = __in6_dev_get(dev);
	if (in6_dev) {
		in6_dev->cnf.mc_forwarding--;
		inet6_netconf_notify_devconf(dev_net(dev), RTM_NEWNETCONF,
					     NETCONFA_MC_FORWARDING,
					     dev->ifindex, &in6_dev->cnf);
	}

	if ((v->flags & MIFF_REGISTER) && !notify)
		unregister_netdevice_queue(dev, head);

	dev_put(dev);
	return 0;
}