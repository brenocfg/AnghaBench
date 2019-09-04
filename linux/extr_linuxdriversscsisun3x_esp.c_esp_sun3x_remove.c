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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct esp {TYPE_1__* host; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_INT_ENAB ; 
 struct esp* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct esp*) ; 
 int /*<<< orphan*/  scsi_esp_unregister (struct esp*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 

__attribute__((used)) static int esp_sun3x_remove(struct platform_device *dev)
{
	struct esp *esp = dev_get_drvdata(&dev->dev);
	unsigned int irq = esp->host->irq;
	u32 val;

	scsi_esp_unregister(esp);

	/* Disable interrupts.  */
	val = dma_read32(DMA_CSR);
	dma_write32(val & ~DMA_INT_ENAB, DMA_CSR);

	free_irq(irq, esp);
	dma_free_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

	scsi_host_put(esp->host);

	return 0;
}