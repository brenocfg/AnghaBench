#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ dir; int /*<<< orphan*/  nbytes; } ;
struct spi_mem_op {TYPE_5__ data; } ;
struct TYPE_10__ {struct device* parent; } ;
struct spi_controller {TYPE_4__ dev; TYPE_3__* dma_rx; TYPE_6__* dma_tx; } ;
struct sg_table {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_12__ {TYPE_1__* device; } ;
struct TYPE_9__ {TYPE_2__* device; } ;
struct TYPE_8__ {struct device* dev; } ;
struct TYPE_7__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 int /*<<< orphan*/  spi_unmap_buf (struct spi_controller*,struct device*,struct sg_table*,int /*<<< orphan*/ ) ; 

void spi_controller_dma_unmap_mem_op_data(struct spi_controller *ctlr,
					  const struct spi_mem_op *op,
					  struct sg_table *sgt)
{
	struct device *dmadev;

	if (!op->data.nbytes)
		return;

	if (op->data.dir == SPI_MEM_DATA_OUT && ctlr->dma_tx)
		dmadev = ctlr->dma_tx->device->dev;
	else if (op->data.dir == SPI_MEM_DATA_IN && ctlr->dma_rx)
		dmadev = ctlr->dma_rx->device->dev;
	else
		dmadev = ctlr->dev.parent;

	spi_unmap_buf(ctlr, dmadev, sgt,
		      op->data.dir == SPI_MEM_DATA_IN ?
		      DMA_FROM_DEVICE : DMA_TO_DEVICE);
}