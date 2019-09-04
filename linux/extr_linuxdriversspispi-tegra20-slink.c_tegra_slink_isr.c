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
struct tegra_slink_data {int status_reg; int cur_direction; int tx_status; int rx_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DATA_DIR_RX ; 
 int DATA_DIR_TX ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int SLINK_RX_OVF ; 
 int SLINK_RX_UNF ; 
 int /*<<< orphan*/  SLINK_STATUS ; 
 int SLINK_TX_OVF ; 
 int SLINK_TX_UNF ; 
 int /*<<< orphan*/  tegra_slink_clear_status (struct tegra_slink_data*) ; 
 int tegra_slink_readl (struct tegra_slink_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_slink_isr(int irq, void *context_data)
{
	struct tegra_slink_data *tspi = context_data;

	tspi->status_reg = tegra_slink_readl(tspi, SLINK_STATUS);
	if (tspi->cur_direction & DATA_DIR_TX)
		tspi->tx_status = tspi->status_reg &
					(SLINK_TX_OVF | SLINK_TX_UNF);

	if (tspi->cur_direction & DATA_DIR_RX)
		tspi->rx_status = tspi->status_reg &
					(SLINK_RX_OVF | SLINK_RX_UNF);
	tegra_slink_clear_status(tspi);

	return IRQ_WAKE_THREAD;
}