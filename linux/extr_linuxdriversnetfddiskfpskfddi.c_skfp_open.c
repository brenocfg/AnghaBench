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
struct TYPE_3__ {int /*<<< orphan*/  a; } ;
struct TYPE_4__ {TYPE_1__ fddi_canon_addr; } ;
struct s_smc {TYPE_2__ hw; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  RX_DISABLE_PROMISC ; 
 int /*<<< orphan*/  STI_FBI () ; 
 int /*<<< orphan*/  init_smt (struct s_smc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_clear_multicast (struct s_smc*) ; 
 int /*<<< orphan*/  mac_drv_rx_mode (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  read_address (struct s_smc*,int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  skfp_interrupt ; 
 int /*<<< orphan*/  smt_online (struct s_smc*,int) ; 

__attribute__((used)) static int skfp_open(struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	int err;

	pr_debug("entering skfp_open\n");
	/* Register IRQ - support shared interrupts by passing device ptr */
	err = request_irq(dev->irq, skfp_interrupt, IRQF_SHARED,
			  dev->name, dev);
	if (err)
		return err;

	/*
	 * Set current address to factory MAC address
	 *
	 * Note: We've already done this step in skfp_driver_init.
	 *       However, it's possible that a user has set a node
	 *               address override, then closed and reopened the
	 *               adapter.  Unless we reset the device address field
	 *               now, we'll continue to use the existing modified
	 *               address.
	 */
	read_address(smc, NULL);
	memcpy(dev->dev_addr, smc->hw.fddi_canon_addr.a, ETH_ALEN);

	init_smt(smc, NULL);
	smt_online(smc, 1);
	STI_FBI();

	/* Clear local multicast address tables */
	mac_clear_multicast(smc);

	/* Disable promiscuous filter settings */
	mac_drv_rx_mode(smc, RX_DISABLE_PROMISC);

	netif_start_queue(dev);
	return 0;
}