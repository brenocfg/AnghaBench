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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {int features; scalar_t__ reg_state; int ifindex; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  NETDEV_REGISTER ; 
 int /*<<< orphan*/  NETDEV_UNREGISTER ; 
 int NETIF_F_NETNS_LOCAL ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  RTM_DELLINK ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __dev_get_by_index (struct net*,int) ; 
 scalar_t__ __dev_get_by_name (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int dev_get_valid_name (struct net*,struct net_device*,char const*) ; 
 int /*<<< orphan*/  dev_mc_flush (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int dev_new_index (struct net*) ; 
 int /*<<< orphan*/  dev_shutdown (struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_flush (struct net_device*) ; 
 int device_rename (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_netdevice (struct net_device*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  netdev_adjacent_add_links (struct net_device*) ; 
 int /*<<< orphan*/  netdev_adjacent_del_links (struct net_device*) ; 
 int peernet2id_alloc (int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  rtmsg_ifinfo (int /*<<< orphan*/ ,struct net_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtmsg_ifinfo_newnet (int /*<<< orphan*/ ,struct net_device*,unsigned int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  unlist_netdevice (struct net_device*) ; 

int dev_change_net_namespace(struct net_device *dev, struct net *net, const char *pat)
{
	int err, new_nsid, new_ifindex;

	ASSERT_RTNL();

	/* Don't allow namespace local devices to be moved. */
	err = -EINVAL;
	if (dev->features & NETIF_F_NETNS_LOCAL)
		goto out;

	/* Ensure the device has been registrered */
	if (dev->reg_state != NETREG_REGISTERED)
		goto out;

	/* Get out if there is nothing todo */
	err = 0;
	if (net_eq(dev_net(dev), net))
		goto out;

	/* Pick the destination device name, and ensure
	 * we can use it in the destination network namespace.
	 */
	err = -EEXIST;
	if (__dev_get_by_name(net, dev->name)) {
		/* We get here if we can't use the current device name */
		if (!pat)
			goto out;
		err = dev_get_valid_name(net, dev, pat);
		if (err < 0)
			goto out;
	}

	/*
	 * And now a mini version of register_netdevice unregister_netdevice.
	 */

	/* If device is running close it first. */
	dev_close(dev);

	/* And unlink it from device chain */
	unlist_netdevice(dev);

	synchronize_net();

	/* Shutdown queueing discipline. */
	dev_shutdown(dev);

	/* Notify protocols, that we are about to destroy
	 * this device. They should clean all the things.
	 *
	 * Note that dev->reg_state stays at NETREG_REGISTERED.
	 * This is wanted because this way 8021q and macvlan know
	 * the device is just moving and can keep their slaves up.
	 */
	call_netdevice_notifiers(NETDEV_UNREGISTER, dev);
	rcu_barrier();

	new_nsid = peernet2id_alloc(dev_net(dev), net, GFP_KERNEL);
	/* If there is an ifindex conflict assign a new one */
	if (__dev_get_by_index(net, dev->ifindex))
		new_ifindex = dev_new_index(net);
	else
		new_ifindex = dev->ifindex;

	rtmsg_ifinfo_newnet(RTM_DELLINK, dev, ~0U, GFP_KERNEL, &new_nsid,
			    new_ifindex);

	/*
	 *	Flush the unicast and multicast chains
	 */
	dev_uc_flush(dev);
	dev_mc_flush(dev);

	/* Send a netdev-removed uevent to the old namespace */
	kobject_uevent(&dev->dev.kobj, KOBJ_REMOVE);
	netdev_adjacent_del_links(dev);

	/* Actually switch the network namespace */
	dev_net_set(dev, net);
	dev->ifindex = new_ifindex;

	/* Send a netdev-add uevent to the new namespace */
	kobject_uevent(&dev->dev.kobj, KOBJ_ADD);
	netdev_adjacent_add_links(dev);

	/* Fixup kobjects */
	err = device_rename(&dev->dev, dev->name);
	WARN_ON(err);

	/* Add the device back in the hashes */
	list_netdevice(dev);

	/* Notify protocols, that a new device appeared. */
	call_netdevice_notifiers(NETDEV_REGISTER, dev);

	/*
	 *	Prevent userspace races by waiting until the network
	 *	device is fully setup before sending notifications.
	 */
	rtmsg_ifinfo(RTM_NEWLINK, dev, ~0U, GFP_KERNEL);

	synchronize_net();
	err = 0;
out:
	return err;
}