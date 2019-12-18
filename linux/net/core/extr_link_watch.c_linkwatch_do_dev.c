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
struct net_device {int flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  __LINK_STATE_LINKWATCH_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_activate (struct net_device*) ; 
 int /*<<< orphan*/  dev_deactivate (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  rfc2863_policy (struct net_device*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void linkwatch_do_dev(struct net_device *dev)
{
	/*
	 * Make sure the above read is complete since it can be
	 * rewritten as soon as we clear the bit below.
	 */
	smp_mb__before_atomic();

	/* We are about to handle this device,
	 * so new events can be accepted
	 */
	clear_bit(__LINK_STATE_LINKWATCH_PENDING, &dev->state);

	rfc2863_policy(dev);
	if (dev->flags & IFF_UP && netif_device_present(dev)) {
		if (netif_carrier_ok(dev))
			dev_activate(dev);
		else
			dev_deactivate(dev);

		netdev_state_change(dev);
	}
	dev_put(dev);
}