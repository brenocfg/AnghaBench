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
struct net_local {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  deferred; int /*<<< orphan*/  immediate; int /*<<< orphan*/  nibble; int /*<<< orphan*/  trigger; scalar_t__ port_owner; } ;
struct net_device {int tx_queue_len; int flags; int irq; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIP_NIBBLE_WAIT ; 
 int /*<<< orphan*/  PLIP_TRIGGER_WAIT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  plip_bh ; 
 int /*<<< orphan*/  plip_header_ops ; 
 int /*<<< orphan*/  plip_kick_bh ; 
 int /*<<< orphan*/  plip_netdev_ops ; 
 int /*<<< orphan*/  plip_timer_bh ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
plip_init_netdev(struct net_device *dev)
{
	struct net_local *nl = netdev_priv(dev);

	/* Then, override parts of it */
	dev->tx_queue_len 	 = 10;
	dev->flags	         = IFF_POINTOPOINT|IFF_NOARP;
	memset(dev->dev_addr, 0xfc, ETH_ALEN);

	dev->netdev_ops		 = &plip_netdev_ops;
	dev->header_ops          = &plip_header_ops;


	nl->port_owner = 0;

	/* Initialize constants */
	nl->trigger	= PLIP_TRIGGER_WAIT;
	nl->nibble	= PLIP_NIBBLE_WAIT;

	/* Initialize task queue structures */
	INIT_WORK(&nl->immediate, plip_bh);
	INIT_DELAYED_WORK(&nl->deferred, plip_kick_bh);

	if (dev->irq == -1)
		INIT_DELAYED_WORK(&nl->timer, plip_timer_bh);

	spin_lock_init(&nl->lock);
}