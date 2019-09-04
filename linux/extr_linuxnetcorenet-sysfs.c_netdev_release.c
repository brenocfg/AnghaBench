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
struct net_device {scalar_t__ reg_state; int /*<<< orphan*/  ifalias; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NETREG_RELEASED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_freemem (struct net_device*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static void netdev_release(struct device *d)
{
	struct net_device *dev = to_net_dev(d);

	BUG_ON(dev->reg_state != NETREG_RELEASED);

	/* no need to wait for rcu grace period:
	 * device is dead and about to be freed.
	 */
	kfree(rcu_access_pointer(dev->ifalias));
	netdev_freemem(dev);
}