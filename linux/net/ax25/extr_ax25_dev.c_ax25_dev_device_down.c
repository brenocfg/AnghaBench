#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/ * ax25_ptr; } ;
struct TYPE_7__ {struct TYPE_7__* next; struct net_device* forward; } ;
typedef  TYPE_1__ ax25_dev ;

/* Variables and functions */
 TYPE_1__* ax25_dev_ax25dev (struct net_device*) ; 
 TYPE_1__* ax25_dev_list ; 
 int /*<<< orphan*/  ax25_dev_lock ; 
 int /*<<< orphan*/  ax25_ds_del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_unregister_dev_sysctl (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ax25_dev_device_down(struct net_device *dev)
{
	ax25_dev *s, *ax25_dev;

	if ((ax25_dev = ax25_dev_ax25dev(dev)) == NULL)
		return;

	ax25_unregister_dev_sysctl(ax25_dev);

	spin_lock_bh(&ax25_dev_lock);

#ifdef CONFIG_AX25_DAMA_SLAVE
	ax25_ds_del_timer(ax25_dev);
#endif

	/*
	 *	Remove any packet forwarding that points to this device.
	 */
	for (s = ax25_dev_list; s != NULL; s = s->next)
		if (s->forward == dev)
			s->forward = NULL;

	if ((s = ax25_dev_list) == ax25_dev) {
		ax25_dev_list = s->next;
		spin_unlock_bh(&ax25_dev_lock);
		dev->ax25_ptr = NULL;
		dev_put(dev);
		kfree(ax25_dev);
		return;
	}

	while (s != NULL && s->next != NULL) {
		if (s->next == ax25_dev) {
			s->next = ax25_dev->next;
			spin_unlock_bh(&ax25_dev_lock);
			dev->ax25_ptr = NULL;
			dev_put(dev);
			kfree(ax25_dev);
			return;
		}

		s = s->next;
	}
	spin_unlock_bh(&ax25_dev_lock);
	dev->ax25_ptr = NULL;
}