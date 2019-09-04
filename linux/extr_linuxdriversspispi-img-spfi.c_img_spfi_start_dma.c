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
struct TYPE_4__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_3__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct spi_transfer {int len; scalar_t__ tx_buf; scalar_t__ rx_buf; TYPE_2__ tx_sg; TYPE_1__ rx_sg; } ;
struct spi_master {int dummy; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct img_spfi {int rx_dma_busy; int tx_dma_busy; int /*<<< orphan*/  tx_ch; int /*<<< orphan*/  rx_ch; scalar_t__ phys; } ;
struct dma_slave_config {int src_addr_width; int src_maxburst; int dst_addr_width; int dst_maxburst; scalar_t__ dst_addr; void* direction; scalar_t__ src_addr; } ;
struct dma_async_tx_descriptor {struct img_spfi* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 void* DMA_DEV_TO_MEM ; 
 void* DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int EIO ; 
 scalar_t__ SPFI_RX_32BIT_VALID_DATA ; 
 scalar_t__ SPFI_RX_8BIT_VALID_DATA ; 
 scalar_t__ SPFI_TX_32BIT_VALID_DATA ; 
 scalar_t__ SPFI_TX_8BIT_VALID_DATA ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spfi_dma_rx_cb ; 
 int /*<<< orphan*/  img_spfi_dma_tx_cb ; 
 int /*<<< orphan*/  spfi_start (struct img_spfi*) ; 
 struct img_spfi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int img_spfi_start_dma(struct spi_master *master,
			      struct spi_device *spi,
			      struct spi_transfer *xfer)
{
	struct img_spfi *spfi = spi_master_get_devdata(spi->master);
	struct dma_async_tx_descriptor *rxdesc = NULL, *txdesc = NULL;
	struct dma_slave_config rxconf, txconf;

	spfi->rx_dma_busy = false;
	spfi->tx_dma_busy = false;

	if (xfer->rx_buf) {
		rxconf.direction = DMA_DEV_TO_MEM;
		if (xfer->len % 4 == 0) {
			rxconf.src_addr = spfi->phys + SPFI_RX_32BIT_VALID_DATA;
			rxconf.src_addr_width = 4;
			rxconf.src_maxburst = 4;
		} else {
			rxconf.src_addr = spfi->phys + SPFI_RX_8BIT_VALID_DATA;
			rxconf.src_addr_width = 1;
			rxconf.src_maxburst = 4;
		}
		dmaengine_slave_config(spfi->rx_ch, &rxconf);

		rxdesc = dmaengine_prep_slave_sg(spfi->rx_ch, xfer->rx_sg.sgl,
						 xfer->rx_sg.nents,
						 DMA_DEV_TO_MEM,
						 DMA_PREP_INTERRUPT);
		if (!rxdesc)
			goto stop_dma;

		rxdesc->callback = img_spfi_dma_rx_cb;
		rxdesc->callback_param = spfi;
	}

	if (xfer->tx_buf) {
		txconf.direction = DMA_MEM_TO_DEV;
		if (xfer->len % 4 == 0) {
			txconf.dst_addr = spfi->phys + SPFI_TX_32BIT_VALID_DATA;
			txconf.dst_addr_width = 4;
			txconf.dst_maxburst = 4;
		} else {
			txconf.dst_addr = spfi->phys + SPFI_TX_8BIT_VALID_DATA;
			txconf.dst_addr_width = 1;
			txconf.dst_maxburst = 4;
		}
		dmaengine_slave_config(spfi->tx_ch, &txconf);

		txdesc = dmaengine_prep_slave_sg(spfi->tx_ch, xfer->tx_sg.sgl,
						 xfer->tx_sg.nents,
						 DMA_MEM_TO_DEV,
						 DMA_PREP_INTERRUPT);
		if (!txdesc)
			goto stop_dma;

		txdesc->callback = img_spfi_dma_tx_cb;
		txdesc->callback_param = spfi;
	}

	if (xfer->rx_buf) {
		spfi->rx_dma_busy = true;
		dmaengine_submit(rxdesc);
		dma_async_issue_pending(spfi->rx_ch);
	}

	spfi_start(spfi);

	if (xfer->tx_buf) {
		spfi->tx_dma_busy = true;
		dmaengine_submit(txdesc);
		dma_async_issue_pending(spfi->tx_ch);
	}

	return 1;

stop_dma:
	dmaengine_terminate_all(spfi->rx_ch);
	dmaengine_terminate_all(spfi->tx_ch);
	return -EIO;
}