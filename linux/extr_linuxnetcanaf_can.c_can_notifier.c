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
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; int /*<<< orphan*/  name; struct can_dev_rcv_lists* ml_priv; } ;
struct can_dev_rcv_lists {int remove_on_zero_entries; int /*<<< orphan*/  entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  can_rcvlists_lock; } ;
struct TYPE_4__ {TYPE_1__ can; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int /*<<< orphan*/  BUG_ON (struct can_dev_rcv_lists*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 TYPE_2__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct can_dev_rcv_lists*) ; 
 struct can_dev_rcv_lists* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int can_notifier(struct notifier_block *nb, unsigned long msg,
			void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct can_dev_rcv_lists *d;

	if (dev->type != ARPHRD_CAN)
		return NOTIFY_DONE;

	switch (msg) {

	case NETDEV_REGISTER:

		/* create new dev_rcv_lists for this device */
		d = kzalloc(sizeof(*d), GFP_KERNEL);
		if (!d)
			return NOTIFY_DONE;
		BUG_ON(dev->ml_priv);
		dev->ml_priv = d;

		break;

	case NETDEV_UNREGISTER:
		spin_lock(&dev_net(dev)->can.can_rcvlists_lock);

		d = dev->ml_priv;
		if (d) {
			if (d->entries)
				d->remove_on_zero_entries = 1;
			else {
				kfree(d);
				dev->ml_priv = NULL;
			}
		} else
			pr_err("can: notifier: receive list not found for dev "
			       "%s\n", dev->name);

		spin_unlock(&dev_net(dev)->can.can_rcvlists_lock);

		break;
	}

	return NOTIFY_DONE;
}