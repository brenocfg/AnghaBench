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
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; int /*<<< orphan*/  mpls_ptr; } ;
struct mpls_dev {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_IP6GRE ; 
 scalar_t__ ARPHRD_IPGRE ; 
 scalar_t__ ARPHRD_LOOPBACK ; 
 scalar_t__ ARPHRD_SIT ; 
 scalar_t__ ARPHRD_TUNNEL ; 
 unsigned int IFF_LOWER_UP ; 
 unsigned int IFF_RUNNING ; 
 scalar_t__ IS_ERR (struct mpls_dev*) ; 
#define  NETDEV_CHANGE 132 
#define  NETDEV_CHANGENAME 131 
#define  NETDEV_DOWN 130 
 unsigned long NETDEV_REGISTER ; 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_OK ; 
 int PTR_ERR (struct mpls_dev*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int dev_get_flags (struct net_device*) ; 
 struct mpls_dev* mpls_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  mpls_dev_destroy_rcu ; 
 struct mpls_dev* mpls_dev_get (struct net_device*) ; 
 int mpls_dev_sysctl_register (struct net_device*,struct mpls_dev*) ; 
 int /*<<< orphan*/  mpls_dev_sysctl_unregister (struct net_device*,struct mpls_dev*) ; 
 int /*<<< orphan*/  mpls_ifdown (struct net_device*,unsigned long) ; 
 int /*<<< orphan*/  mpls_ifup (struct net_device*,int) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int notifier_from_errno (int) ; 

__attribute__((used)) static int mpls_dev_notify(struct notifier_block *this, unsigned long event,
			   void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct mpls_dev *mdev;
	unsigned int flags;

	if (event == NETDEV_REGISTER) {

		/* For now just support Ethernet, IPGRE, IP6GRE, SIT and
		 * IPIP devices
		 */
		if (dev->type == ARPHRD_ETHER ||
		    dev->type == ARPHRD_LOOPBACK ||
		    dev->type == ARPHRD_IPGRE ||
		    dev->type == ARPHRD_IP6GRE ||
		    dev->type == ARPHRD_SIT ||
		    dev->type == ARPHRD_TUNNEL) {
			mdev = mpls_add_dev(dev);
			if (IS_ERR(mdev))
				return notifier_from_errno(PTR_ERR(mdev));
		}
		return NOTIFY_OK;
	}

	mdev = mpls_dev_get(dev);
	if (!mdev)
		return NOTIFY_OK;

	switch (event) {
	case NETDEV_DOWN:
		mpls_ifdown(dev, event);
		break;
	case NETDEV_UP:
		flags = dev_get_flags(dev);
		if (flags & (IFF_RUNNING | IFF_LOWER_UP))
			mpls_ifup(dev, RTNH_F_DEAD | RTNH_F_LINKDOWN);
		else
			mpls_ifup(dev, RTNH_F_DEAD);
		break;
	case NETDEV_CHANGE:
		flags = dev_get_flags(dev);
		if (flags & (IFF_RUNNING | IFF_LOWER_UP))
			mpls_ifup(dev, RTNH_F_DEAD | RTNH_F_LINKDOWN);
		else
			mpls_ifdown(dev, event);
		break;
	case NETDEV_UNREGISTER:
		mpls_ifdown(dev, event);
		mdev = mpls_dev_get(dev);
		if (mdev) {
			mpls_dev_sysctl_unregister(dev, mdev);
			RCU_INIT_POINTER(dev->mpls_ptr, NULL);
			call_rcu(&mdev->rcu, mpls_dev_destroy_rcu);
		}
		break;
	case NETDEV_CHANGENAME:
		mdev = mpls_dev_get(dev);
		if (mdev) {
			int err;

			mpls_dev_sysctl_unregister(dev, mdev);
			err = mpls_dev_sysctl_register(dev, mdev);
			if (err)
				return notifier_from_errno(err);
		}
		break;
	}
	return NOTIFY_OK;
}