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
struct smsc9420_pdata {scalar_t__ rx_ring_tail; scalar_t__ rx_ring_head; TYPE_2__* rx_buffers; TYPE_1__* rx_ring; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {scalar_t__ mapping; scalar_t__ skb; } ;
struct TYPE_3__ {scalar_t__ buffer2; scalar_t__ buffer1; scalar_t__ length; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void smsc9420_free_rx_ring(struct smsc9420_pdata *pd)
{
	int i;

	BUG_ON(!pd->rx_ring);

	if (!pd->rx_buffers)
		return;

	for (i = 0; i < RX_RING_SIZE; i++) {
		if (pd->rx_buffers[i].skb)
			dev_kfree_skb_any(pd->rx_buffers[i].skb);

		if (pd->rx_buffers[i].mapping)
			pci_unmap_single(pd->pdev, pd->rx_buffers[i].mapping,
				PKT_BUF_SZ, PCI_DMA_FROMDEVICE);

		pd->rx_ring[i].status = 0;
		pd->rx_ring[i].length = 0;
		pd->rx_ring[i].buffer1 = 0;
		pd->rx_ring[i].buffer2 = 0;
	}
	wmb();

	kfree(pd->rx_buffers);
	pd->rx_buffers = NULL;

	pd->rx_ring_head = 0;
	pd->rx_ring_tail = 0;
}