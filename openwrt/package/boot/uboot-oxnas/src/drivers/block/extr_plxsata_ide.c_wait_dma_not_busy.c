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

/* Variables and functions */
 scalar_t__ DMA_CTRL_STATUS ; 
 unsigned int DMA_CTRL_STATUS_RESET ; 
 int MAX_DMA_ABORT_LOOPS ; 
 int MAX_DMA_XFER_LOOPS ; 
 scalar_t__ SATA_DMA_CHANNEL ; 
 int /*<<< orphan*/  dma_busy () ; 
 int /*<<< orphan*/  printf (char*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int wait_dma_not_busy(int device)
{
	unsigned int cleanup_required = 0;

	/* Poll for DMA completion */
	int loops = MAX_DMA_XFER_LOOPS;
	do {
		if (!dma_busy()) {
			break;
		}
		udelay(100);
	} while (--loops);

	if (!loops) {
		printf("wait_dma_not_busy() Timed out of wait for DMA not busy\n");
		cleanup_required = 1;
	}

	if (cleanup_required) {
		/* Abort DMA to make sure it has finished. */
		unsigned int ctrl_status = readl(
			SATA_DMA_CHANNEL + DMA_CTRL_STATUS);
		ctrl_status |= DMA_CTRL_STATUS_RESET;
		writel(ctrl_status, SATA_DMA_CHANNEL + DMA_CTRL_STATUS);

		// Wait for the channel to become idle - should be quick as should
		// finish after the next AHB single or burst transfer
		loops = MAX_DMA_ABORT_LOOPS;
		do {
			if (!dma_busy()) {
				break;
			}
			udelay(10);
		} while (--loops);

		if (!loops) {
			printf("wait_dma_not_busy() Timed out of wait for DMA channel abort\n");
		} else {
			/* Successfully cleanup the DMA channel */
			cleanup_required = 0;
		}

		// Deassert reset for the channel
		ctrl_status = readl(SATA_DMA_CHANNEL + DMA_CTRL_STATUS);
		ctrl_status &= ~DMA_CTRL_STATUS_RESET;
		writel(ctrl_status, SATA_DMA_CHANNEL + DMA_CTRL_STATUS);
	}

	return !cleanup_required;
}