#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  QueueSkb; int /*<<< orphan*/  SendSkbQueue; } ;
struct s_smc {TYPE_1__ os; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
typedef  TYPE_1__ skfddi_priv ;

/* Variables and functions */
 int /*<<< orphan*/  CLI_FBI () ; 
 int /*<<< orphan*/  MAX_TX_QUEUE_LEN ; 
 int /*<<< orphan*/  card_stop (struct s_smc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mac_drv_clear_rx_queue (struct s_smc*) ; 
 int /*<<< orphan*/  mac_drv_clear_tx_queue (struct s_smc*) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smt_reset_defaults (struct s_smc*,int) ; 

__attribute__((used)) static int skfp_close(struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;

	CLI_FBI();
	smt_reset_defaults(smc, 1);
	card_stop(smc);
	mac_drv_clear_tx_queue(smc);
	mac_drv_clear_rx_queue(smc);

	netif_stop_queue(dev);
	/* Deregister (free) IRQ */
	free_irq(dev->irq, dev);

	skb_queue_purge(&bp->SendSkbQueue);
	bp->QueueSkb = MAX_TX_QUEUE_LEN;

	return 0;
}