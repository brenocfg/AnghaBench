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
struct tegra_spi_data {int status_reg; int cur_direction; int tx_status; int rx_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DATA_DIR_RX ; 
 int DATA_DIR_TX ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  SPI_FIFO_STATUS ; 
 int SPI_RX_FIFO_OVF ; 
 int SPI_RX_FIFO_UNF ; 
 int SPI_TX_FIFO_OVF ; 
 int SPI_TX_FIFO_UNF ; 
 int /*<<< orphan*/  tegra_spi_clear_status (struct tegra_spi_data*) ; 
 int tegra_spi_readl (struct tegra_spi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_spi_isr(int irq, void *context_data)
{
	struct tegra_spi_data *tspi = context_data;

	tspi->status_reg = tegra_spi_readl(tspi, SPI_FIFO_STATUS);
	if (tspi->cur_direction & DATA_DIR_TX)
		tspi->tx_status = tspi->status_reg &
					(SPI_TX_FIFO_UNF | SPI_TX_FIFO_OVF);

	if (tspi->cur_direction & DATA_DIR_RX)
		tspi->rx_status = tspi->status_reg &
					(SPI_RX_FIFO_OVF | SPI_RX_FIFO_UNF);
	tegra_spi_clear_status(tspi);

	return IRQ_WAKE_THREAD;
}