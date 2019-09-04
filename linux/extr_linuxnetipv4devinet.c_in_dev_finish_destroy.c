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
struct net_device {int dummy; } ;
struct in_device {int /*<<< orphan*/  dead; int /*<<< orphan*/  mc_hash; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  ifa_list; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct in_device*) ; 
 int /*<<< orphan*/  pr_err (char*,struct in_device*) ; 
 struct in_device* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

void in_dev_finish_destroy(struct in_device *idev)
{
	struct net_device *dev = idev->dev;

	WARN_ON(idev->ifa_list);
	WARN_ON(idev->mc_list);
	kfree(rcu_dereference_protected(idev->mc_hash, 1));
#ifdef NET_REFCNT_DEBUG
	pr_debug("%s: %p=%s\n", __func__, idev, dev ? dev->name : "NIL");
#endif
	dev_put(dev);
	if (!idev->dead)
		pr_err("Freeing alive in_device %p\n", idev);
	else
		kfree(idev);
}