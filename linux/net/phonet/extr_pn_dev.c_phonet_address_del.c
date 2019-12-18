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
typedef  int u8 ;
struct phonet_device_list {int /*<<< orphan*/  lock; } ;
struct phonet_device {int /*<<< orphan*/  list; int /*<<< orphan*/  addrs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 struct phonet_device* __phonet_get (struct net_device*) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct phonet_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phonet_device_list* phonet_device_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

int phonet_address_del(struct net_device *dev, u8 addr)
{
	struct phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	struct phonet_device *pnd;
	int err = 0;

	mutex_lock(&pndevs->lock);
	pnd = __phonet_get(dev);
	if (!pnd || !test_and_clear_bit(addr >> 2, pnd->addrs)) {
		err = -EADDRNOTAVAIL;
		pnd = NULL;
	} else if (bitmap_empty(pnd->addrs, 64))
		list_del_rcu(&pnd->list);
	else
		pnd = NULL;
	mutex_unlock(&pndevs->lock);

	if (pnd)
		kfree_rcu(pnd, rcu);

	return err;
}