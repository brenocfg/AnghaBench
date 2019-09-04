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
struct tc35815_local {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc35815_chip_init (struct net_device*) ; 
 int /*<<< orphan*/  tc35815_chip_reset (struct net_device*) ; 
 scalar_t__ tc35815_init_queues (struct net_device*) ; 
 int /*<<< orphan*/  tc35815_interrupt ; 

__attribute__((used)) static int
tc35815_open(struct net_device *dev)
{
	struct tc35815_local *lp = netdev_priv(dev);

	/*
	 * This is used if the interrupt line can turned off (shared).
	 * See 3c503.c for an example of selecting the IRQ at config-time.
	 */
	if (request_irq(dev->irq, tc35815_interrupt, IRQF_SHARED,
			dev->name, dev))
		return -EAGAIN;

	tc35815_chip_reset(dev);

	if (tc35815_init_queues(dev) != 0) {
		free_irq(dev->irq, dev);
		return -EAGAIN;
	}

	napi_enable(&lp->napi);

	/* Reset the hardware here. Don't forget to set the station address. */
	spin_lock_irq(&lp->lock);
	tc35815_chip_init(dev);
	spin_unlock_irq(&lp->lock);

	netif_carrier_off(dev);
	/* schedule a link state check */
	phy_start(dev->phydev);

	/* We are now ready to accept transmit requeusts from
	 * the queueing layer of the networking.
	 */
	netif_start_queue(dev);

	return 0;
}