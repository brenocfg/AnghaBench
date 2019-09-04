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
struct usbhs_fifo {int /*<<< orphan*/  rx_slave; void* rx_chan; int /*<<< orphan*/  tx_slave; void* tx_chan; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 void* dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbhsf_dma_filter ; 

__attribute__((used)) static void usbhsf_dma_init_pdev(struct usbhs_fifo *fifo)
{
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	fifo->tx_chan = dma_request_channel(mask, usbhsf_dma_filter,
					    &fifo->tx_slave);

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	fifo->rx_chan = dma_request_channel(mask, usbhsf_dma_filter,
					    &fifo->rx_slave);
}