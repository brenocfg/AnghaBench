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
typedef  int u32 ;
struct stm32_spi {scalar_t__ cur_comm; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_rx; scalar_t__ rx_buf; scalar_t__ base; int /*<<< orphan*/  dma_tx; scalar_t__ tx_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_3__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct spi_transfer {TYPE_2__ tx_sg; TYPE_1__ rx_sg; } ;
struct dma_slave_config {int /*<<< orphan*/  direction; } ;
struct dma_async_tx_descriptor {struct stm32_spi* callback_param; void* callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  SPI_CFG1_RXDMAEN ; 
 int /*<<< orphan*/  SPI_CFG1_TXDMAEN ; 
 int /*<<< orphan*/  SPI_CR1_CSTART ; 
 int SPI_IER_EOTIE ; 
 int SPI_IER_MODFIE ; 
 int SPI_IER_OVRIE ; 
 int SPI_IER_TXTFIE ; 
 scalar_t__ SPI_SIMPLEX_TX ; 
 int /*<<< orphan*/  STM32_SPI_CFG1 ; 
 int /*<<< orphan*/  STM32_SPI_CR1 ; 
 scalar_t__ STM32_SPI_IER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_spi_clr_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stm32_spi_dma_cb ; 
 int /*<<< orphan*/  stm32_spi_dma_config (struct stm32_spi*,struct dma_slave_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_spi_enable (struct stm32_spi*) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stm32_spi_transfer_one_irq (struct stm32_spi*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32_spi_transfer_one_dma(struct stm32_spi *spi,
				      struct spi_transfer *xfer)
{
	struct dma_slave_config tx_dma_conf, rx_dma_conf;
	struct dma_async_tx_descriptor *tx_dma_desc, *rx_dma_desc;
	unsigned long flags;
	u32 ier = 0;

	spin_lock_irqsave(&spi->lock, flags);

	rx_dma_desc = NULL;
	if (spi->rx_buf) {
		stm32_spi_dma_config(spi, &rx_dma_conf, DMA_DEV_TO_MEM);
		dmaengine_slave_config(spi->dma_rx, &rx_dma_conf);

		/* Enable Rx DMA request */
		stm32_spi_set_bits(spi, STM32_SPI_CFG1, SPI_CFG1_RXDMAEN);

		rx_dma_desc = dmaengine_prep_slave_sg(
					spi->dma_rx, xfer->rx_sg.sgl,
					xfer->rx_sg.nents,
					rx_dma_conf.direction,
					DMA_PREP_INTERRUPT);
	}

	tx_dma_desc = NULL;
	if (spi->tx_buf) {
		stm32_spi_dma_config(spi, &tx_dma_conf, DMA_MEM_TO_DEV);
		dmaengine_slave_config(spi->dma_tx, &tx_dma_conf);

		tx_dma_desc = dmaengine_prep_slave_sg(
					spi->dma_tx, xfer->tx_sg.sgl,
					xfer->tx_sg.nents,
					tx_dma_conf.direction,
					DMA_PREP_INTERRUPT);
	}

	if ((spi->tx_buf && !tx_dma_desc) ||
	    (spi->rx_buf && !rx_dma_desc))
		goto dma_desc_error;

	if (rx_dma_desc) {
		rx_dma_desc->callback = stm32_spi_dma_cb;
		rx_dma_desc->callback_param = spi;

		if (dma_submit_error(dmaengine_submit(rx_dma_desc))) {
			dev_err(spi->dev, "Rx DMA submit failed\n");
			goto dma_desc_error;
		}
		/* Enable Rx DMA channel */
		dma_async_issue_pending(spi->dma_rx);
	}

	if (tx_dma_desc) {
		if (spi->cur_comm == SPI_SIMPLEX_TX) {
			tx_dma_desc->callback = stm32_spi_dma_cb;
			tx_dma_desc->callback_param = spi;
		}

		if (dma_submit_error(dmaengine_submit(tx_dma_desc))) {
			dev_err(spi->dev, "Tx DMA submit failed\n");
			goto dma_submit_error;
		}
		/* Enable Tx DMA channel */
		dma_async_issue_pending(spi->dma_tx);

		/* Enable Tx DMA request */
		stm32_spi_set_bits(spi, STM32_SPI_CFG1, SPI_CFG1_TXDMAEN);
	}

	/* Enable the interrupts relative to the end of transfer */
	ier |= SPI_IER_EOTIE | SPI_IER_TXTFIE |	SPI_IER_OVRIE |	SPI_IER_MODFIE;
	writel_relaxed(ier, spi->base + STM32_SPI_IER);

	stm32_spi_enable(spi);

	stm32_spi_set_bits(spi, STM32_SPI_CR1, SPI_CR1_CSTART);

	spin_unlock_irqrestore(&spi->lock, flags);

	return 1;

dma_submit_error:
	if (spi->rx_buf)
		dmaengine_terminate_all(spi->dma_rx);

dma_desc_error:
	stm32_spi_clr_bits(spi, STM32_SPI_CFG1, SPI_CFG1_RXDMAEN);

	spin_unlock_irqrestore(&spi->lock, flags);

	dev_info(spi->dev, "DMA issue: fall back to irq transfer\n");

	return stm32_spi_transfer_one_irq(spi);
}