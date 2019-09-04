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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;
struct esp {scalar_t__ dmarev; TYPE_1__* host; int /*<<< orphan*/  dma_regs; int /*<<< orphan*/  regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; struct platform_device* dma; } ;
struct TYPE_2__ {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_INT_ENAB ; 
 int /*<<< orphan*/  SBUS_ESP_REG_SIZE ; 
 struct esp* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ dvmahme ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct esp*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_esp_unregister (struct esp*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 

__attribute__((used)) static int esp_sbus_remove(struct platform_device *op)
{
	struct esp *esp = dev_get_drvdata(&op->dev);
	struct platform_device *dma_of = esp->dma;
	unsigned int irq = esp->host->irq;
	bool is_hme;
	u32 val;

	scsi_esp_unregister(esp);

	/* Disable interrupts.  */
	val = dma_read32(DMA_CSR);
	dma_write32(val & ~DMA_INT_ENAB, DMA_CSR);

	free_irq(irq, esp);

	is_hme = (esp->dmarev == dvmahme);

	dma_free_coherent(&op->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);
	of_iounmap(&op->resource[(is_hme ? 1 : 0)], esp->regs,
		   SBUS_ESP_REG_SIZE);
	of_iounmap(&dma_of->resource[0], esp->dma_regs,
		   resource_size(&dma_of->resource[0]));

	scsi_host_put(esp->host);

	dev_set_drvdata(&op->dev, NULL);

	put_device(&dma_of->dev);

	return 0;
}