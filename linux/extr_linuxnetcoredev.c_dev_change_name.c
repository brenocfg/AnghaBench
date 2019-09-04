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
struct net_device {int flags; int priv_flags; char const* name; unsigned char name_assign_type; int /*<<< orphan*/  name_hlist; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int IFF_LIVE_RENAME_OK ; 
 int IFF_UP ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  NETDEV_CHANGENAME ; 
 void* NET_NAME_RENAMED ; 
 int call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  dev_base_lock ; 
 int dev_get_valid_name (struct net*,struct net_device*,char const*) ; 
 int /*<<< orphan*/  dev_name_hash (struct net*,char*) ; 
 struct net* dev_net (struct net_device*) ; 
 int device_rename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  devnet_rename_seq ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  netdev_adjacent_rename_links (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*) ; 
 int notifier_to_errno (int) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int dev_change_name(struct net_device *dev, const char *newname)
{
	unsigned char old_assign_type;
	char oldname[IFNAMSIZ];
	int err = 0;
	int ret;
	struct net *net;

	ASSERT_RTNL();
	BUG_ON(!dev_net(dev));

	net = dev_net(dev);

	/* Some auto-enslaved devices e.g. failover slaves are
	 * special, as userspace might rename the device after
	 * the interface had been brought up and running since
	 * the point kernel initiated auto-enslavement. Allow
	 * live name change even when these slave devices are
	 * up and running.
	 *
	 * Typically, users of these auto-enslaving devices
	 * don't actually care about slave name change, as
	 * they are supposed to operate on master interface
	 * directly.
	 */
	if (dev->flags & IFF_UP &&
	    likely(!(dev->priv_flags & IFF_LIVE_RENAME_OK)))
		return -EBUSY;

	write_seqcount_begin(&devnet_rename_seq);

	if (strncmp(newname, dev->name, IFNAMSIZ) == 0) {
		write_seqcount_end(&devnet_rename_seq);
		return 0;
	}

	memcpy(oldname, dev->name, IFNAMSIZ);

	err = dev_get_valid_name(net, dev, newname);
	if (err < 0) {
		write_seqcount_end(&devnet_rename_seq);
		return err;
	}

	if (oldname[0] && !strchr(oldname, '%'))
		netdev_info(dev, "renamed from %s\n", oldname);

	old_assign_type = dev->name_assign_type;
	dev->name_assign_type = NET_NAME_RENAMED;

rollback:
	ret = device_rename(&dev->dev, dev->name);
	if (ret) {
		memcpy(dev->name, oldname, IFNAMSIZ);
		dev->name_assign_type = old_assign_type;
		write_seqcount_end(&devnet_rename_seq);
		return ret;
	}

	write_seqcount_end(&devnet_rename_seq);

	netdev_adjacent_rename_links(dev, oldname);

	write_lock_bh(&dev_base_lock);
	hlist_del_rcu(&dev->name_hlist);
	write_unlock_bh(&dev_base_lock);

	synchronize_rcu();

	write_lock_bh(&dev_base_lock);
	hlist_add_head_rcu(&dev->name_hlist, dev_name_hash(net, dev->name));
	write_unlock_bh(&dev_base_lock);

	ret = call_netdevice_notifiers(NETDEV_CHANGENAME, dev);
	ret = notifier_to_errno(ret);

	if (ret) {
		/* err >= 0 after dev_alloc_name() or stores the first errno */
		if (err >= 0) {
			err = ret;
			write_seqcount_begin(&devnet_rename_seq);
			memcpy(dev->name, oldname, IFNAMSIZ);
			memcpy(oldname, newname, IFNAMSIZ);
			dev->name_assign_type = old_assign_type;
			old_assign_type = NET_NAME_RENAMED;
			goto rollback;
		} else {
			pr_err("%s: name change rollback failed: %d\n",
			       dev->name, ret);
		}
	}

	return err;
}