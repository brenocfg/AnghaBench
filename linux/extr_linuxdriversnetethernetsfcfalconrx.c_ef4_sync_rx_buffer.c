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
struct ef4_rx_buffer {int /*<<< orphan*/  dma_addr; } ;
struct ef4_nic {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ef4_sync_rx_buffer(struct ef4_nic *efx,
				      struct ef4_rx_buffer *rx_buf,
				      unsigned int len)
{
	dma_sync_single_for_cpu(&efx->pci_dev->dev, rx_buf->dma_addr, len,
				DMA_FROM_DEVICE);
}