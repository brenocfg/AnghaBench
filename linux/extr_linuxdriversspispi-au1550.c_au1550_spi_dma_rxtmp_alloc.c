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
struct au1550_spi {unsigned int dma_rx_tmpbuf_size; scalar_t__ dma_rx_tmpbuf; int /*<<< orphan*/  dma_rx_tmpbuf_addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1550_spi_dma_rxtmp_alloc(struct au1550_spi *hw, unsigned size)
{
	hw->dma_rx_tmpbuf = kmalloc(size, GFP_KERNEL);
	if (!hw->dma_rx_tmpbuf)
		return -ENOMEM;
	hw->dma_rx_tmpbuf_size = size;
	hw->dma_rx_tmpbuf_addr = dma_map_single(hw->dev, hw->dma_rx_tmpbuf,
			size, DMA_FROM_DEVICE);
	if (dma_mapping_error(hw->dev, hw->dma_rx_tmpbuf_addr)) {
		kfree(hw->dma_rx_tmpbuf);
		hw->dma_rx_tmpbuf = 0;
		hw->dma_rx_tmpbuf_size = 0;
		return -EFAULT;
	}
	return 0;
}