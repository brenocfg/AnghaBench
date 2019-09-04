#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rx_lpi_exit_n; int /*<<< orphan*/  rx_lpi_entry_n; int /*<<< orphan*/  tx_lpi_exit_n; int /*<<< orphan*/  tx_lpi_entry_n; } ;
struct sxgbe_priv_data {int tx_path_in_lpi_mode; TYPE_3__ xstats; int /*<<< orphan*/  ioaddr; TYPE_2__* hw; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {TYPE_1__* mac; } ;
struct TYPE_4__ {int (* host_irq_status ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RX_ENTRY_LPI_MODE ; 
 int RX_EXIT_LPI_MODE ; 
 int TX_ENTRY_LPI_MODE ; 
 int TX_EXIT_LPI_MODE ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static irqreturn_t sxgbe_common_interrupt(int irq, void *dev_id)
{
	struct net_device *netdev = (struct net_device *)dev_id;
	struct sxgbe_priv_data *priv = netdev_priv(netdev);
	int status;

	status = priv->hw->mac->host_irq_status(priv->ioaddr, &priv->xstats);
	/* For LPI we need to save the tx status */
	if (status & TX_ENTRY_LPI_MODE) {
		priv->xstats.tx_lpi_entry_n++;
		priv->tx_path_in_lpi_mode = true;
	}
	if (status & TX_EXIT_LPI_MODE) {
		priv->xstats.tx_lpi_exit_n++;
		priv->tx_path_in_lpi_mode = false;
	}
	if (status & RX_ENTRY_LPI_MODE)
		priv->xstats.rx_lpi_entry_n++;
	if (status & RX_EXIT_LPI_MODE)
		priv->xstats.rx_lpi_exit_n++;

	return IRQ_HANDLED;
}