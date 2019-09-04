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
typedef  int u32 ;
struct sh_eth_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; int /*<<< orphan*/  irq_enabled; struct sh_eth_cpu_data* cd; } ;
struct sh_eth_cpu_data {int tx_check; int eesr_err_check; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EESIPR ; 
 int EESIPR_ECIIP ; 
 int /*<<< orphan*/  EESR ; 
 int EESR_ECI ; 
 int EESR_RX_CHECK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_emac_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_error (struct net_device*,int) ; 
 int sh_eth_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_tx_free (struct net_device*,int) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t sh_eth_interrupt(int irq, void *netdev)
{
	struct net_device *ndev = netdev;
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_cpu_data *cd = mdp->cd;
	irqreturn_t ret = IRQ_NONE;
	u32 intr_status, intr_enable;

	spin_lock(&mdp->lock);

	/* Get interrupt status */
	intr_status = sh_eth_read(ndev, EESR);
	/* Mask it with the interrupt mask, forcing ECI interrupt  to be always
	 * enabled since it's the one that  comes  thru regardless of the mask,
	 * and  we need to fully handle it  in sh_eth_emac_interrupt() in order
	 * to quench it as it doesn't get cleared by just writing 1 to the  ECI
	 * bit...
	 */
	intr_enable = sh_eth_read(ndev, EESIPR);
	intr_status &= intr_enable | EESIPR_ECIIP;
	if (intr_status & (EESR_RX_CHECK | cd->tx_check | EESR_ECI |
			   cd->eesr_err_check))
		ret = IRQ_HANDLED;
	else
		goto out;

	if (unlikely(!mdp->irq_enabled)) {
		sh_eth_write(ndev, 0, EESIPR);
		goto out;
	}

	if (intr_status & EESR_RX_CHECK) {
		if (napi_schedule_prep(&mdp->napi)) {
			/* Mask Rx interrupts */
			sh_eth_write(ndev, intr_enable & ~EESR_RX_CHECK,
				     EESIPR);
			__napi_schedule(&mdp->napi);
		} else {
			netdev_warn(ndev,
				    "ignoring interrupt, status 0x%08x, mask 0x%08x.\n",
				    intr_status, intr_enable);
		}
	}

	/* Tx Check */
	if (intr_status & cd->tx_check) {
		/* Clear Tx interrupts */
		sh_eth_write(ndev, intr_status & cd->tx_check, EESR);

		sh_eth_tx_free(ndev, true);
		netif_wake_queue(ndev);
	}

	/* E-MAC interrupt */
	if (intr_status & EESR_ECI)
		sh_eth_emac_interrupt(ndev);

	if (intr_status & cd->eesr_err_check) {
		/* Clear error interrupts */
		sh_eth_write(ndev, intr_status & cd->eesr_err_check, EESR);

		sh_eth_error(ndev, intr_status);
	}

out:
	spin_unlock(&mdp->lock);

	return ret;
}