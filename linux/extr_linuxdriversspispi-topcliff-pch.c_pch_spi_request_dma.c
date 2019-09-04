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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct pch_dma_slave {int chan_id; unsigned int width; scalar_t__ rx_reg; int /*<<< orphan*/ * dma_dev; scalar_t__ tx_reg; } ;
struct pch_spi_dma_ctrl {struct dma_chan* chan_rx; struct dma_chan* chan_tx; struct pch_dma_slave param_rx; struct pch_dma_slave param_tx; } ;
struct pch_spi_data {int ch; scalar_t__ use_dma; TYPE_3__* master; scalar_t__ io_base_addr; TYPE_2__* board_dat; struct pch_spi_dma_ctrl dma; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 unsigned int PCH_DMA_WIDTH_1_BYTE ; 
 unsigned int PCH_DMA_WIDTH_2_BYTES ; 
 scalar_t__ PCH_SPDRR ; 
 scalar_t__ PCH_SPDWR ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 struct dma_chan* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pch_dma_slave*) ; 
 int /*<<< orphan*/  pch_spi_filter ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_spi_request_dma(struct pch_spi_data *data, int bpw)
{
	dma_cap_mask_t mask;
	struct dma_chan *chan;
	struct pci_dev *dma_dev;
	struct pch_dma_slave *param;
	struct pch_spi_dma_ctrl *dma;
	unsigned int width;

	if (bpw == 8)
		width = PCH_DMA_WIDTH_1_BYTE;
	else
		width = PCH_DMA_WIDTH_2_BYTES;

	dma = &data->dma;
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Get DMA's dev information */
	dma_dev = pci_get_slot(data->board_dat->pdev->bus,
			PCI_DEVFN(PCI_SLOT(data->board_dat->pdev->devfn), 0));

	/* Set Tx DMA */
	param = &dma->param_tx;
	param->dma_dev = &dma_dev->dev;
	param->chan_id = data->ch * 2; /* Tx = 0, 2 */;
	param->tx_reg = data->io_base_addr + PCH_SPDWR;
	param->width = width;
	chan = dma_request_channel(mask, pch_spi_filter, param);
	if (!chan) {
		dev_err(&data->master->dev,
			"ERROR: dma_request_channel FAILS(Tx)\n");
		data->use_dma = 0;
		return;
	}
	dma->chan_tx = chan;

	/* Set Rx DMA */
	param = &dma->param_rx;
	param->dma_dev = &dma_dev->dev;
	param->chan_id = data->ch * 2 + 1; /* Rx = Tx + 1 */;
	param->rx_reg = data->io_base_addr + PCH_SPDRR;
	param->width = width;
	chan = dma_request_channel(mask, pch_spi_filter, param);
	if (!chan) {
		dev_err(&data->master->dev,
			"ERROR: dma_request_channel FAILS(Rx)\n");
		dma_release_channel(dma->chan_tx);
		dma->chan_tx = NULL;
		data->use_dma = 0;
		return;
	}
	dma->chan_rx = chan;
}