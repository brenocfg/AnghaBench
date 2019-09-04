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
struct phonet_device_list {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct phonet_device {int /*<<< orphan*/  list; int /*<<< orphan*/  addrs; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct phonet_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct phonet_device_list* phonet_device_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct phonet_device *__phonet_device_alloc(struct net_device *dev)
{
	struct phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	struct phonet_device *pnd = kmalloc(sizeof(*pnd), GFP_ATOMIC);
	if (pnd == NULL)
		return NULL;
	pnd->netdev = dev;
	bitmap_zero(pnd->addrs, 64);

	BUG_ON(!mutex_is_locked(&pndevs->lock));
	list_add_rcu(&pnd->list, &pndevs->list);
	return pnd;
}