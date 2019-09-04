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
struct stm32_spi {scalar_t__ rx_len; int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  dma_rx; scalar_t__ rx_buf; scalar_t__ cur_usedma; int /*<<< orphan*/  dma_tx; scalar_t__ tx_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SPI_CFG1_RXDMAEN ; 
 int SPI_CFG1_TXDMAEN ; 
 int SPI_CR1_CSTART ; 
 int SPI_CR1_CSUSP ; 
 int SPI_CR1_SPE ; 
 int SPI_IFCR_ALL ; 
 int SPI_SR_EOT ; 
 int SPI_SR_SUSP ; 
 scalar_t__ STM32_SPI_CFG1 ; 
 scalar_t__ STM32_SPI_CR1 ; 
 scalar_t__ STM32_SPI_IER ; 
 scalar_t__ STM32_SPI_IFCR ; 
 scalar_t__ STM32_SPI_SR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ readl_relaxed_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,scalar_t__,int) ; 
 int /*<<< orphan*/  stm32_spi_read_rxfifo (struct stm32_spi*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32_spi_disable(struct stm32_spi *spi)
{
	unsigned long flags;
	u32 cr1, sr;

	dev_dbg(spi->dev, "disable controller\n");

	spin_lock_irqsave(&spi->lock, flags);

	cr1 = readl_relaxed(spi->base + STM32_SPI_CR1);

	if (!(cr1 & SPI_CR1_SPE)) {
		spin_unlock_irqrestore(&spi->lock, flags);
		return;
	}

	/* Wait on EOT or suspend the flow */
	if (readl_relaxed_poll_timeout_atomic(spi->base + STM32_SPI_SR,
					      sr, !(sr & SPI_SR_EOT),
					      10, 100000) < 0) {
		if (cr1 & SPI_CR1_CSTART) {
			writel_relaxed(cr1 | SPI_CR1_CSUSP,
				       spi->base + STM32_SPI_CR1);
			if (readl_relaxed_poll_timeout_atomic(
						spi->base + STM32_SPI_SR,
						sr, !(sr & SPI_SR_SUSP),
						10, 100000) < 0)
				dev_warn(spi->dev,
					 "Suspend request timeout\n");
		}
	}

	if (!spi->cur_usedma && spi->rx_buf && (spi->rx_len > 0))
		stm32_spi_read_rxfifo(spi, true);

	if (spi->cur_usedma && spi->tx_buf)
		dmaengine_terminate_all(spi->dma_tx);
	if (spi->cur_usedma && spi->rx_buf)
		dmaengine_terminate_all(spi->dma_rx);

	stm32_spi_clr_bits(spi, STM32_SPI_CR1, SPI_CR1_SPE);

	stm32_spi_clr_bits(spi, STM32_SPI_CFG1, SPI_CFG1_TXDMAEN |
						SPI_CFG1_RXDMAEN);

	/* Disable interrupts and clear status flags */
	writel_relaxed(0, spi->base + STM32_SPI_IER);
	writel_relaxed(SPI_IFCR_ALL, spi->base + STM32_SPI_IFCR);

	spin_unlock_irqrestore(&spi->lock, flags);
}