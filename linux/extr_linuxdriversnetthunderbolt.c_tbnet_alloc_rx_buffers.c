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
struct tbnet_ring {int prod; int /*<<< orphan*/  ring; struct tbnet_frame* frames; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_phy; } ;
struct tbnet_frame {TYPE_1__ frame; int /*<<< orphan*/  dev; scalar_t__ page; } ;
struct tbnet {int /*<<< orphan*/  dev; struct tbnet_ring rx_ring; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int TBNET_RING_SIZE ; 
 int /*<<< orphan*/  TBNET_RX_PAGE_ORDER ; 
 int /*<<< orphan*/  TBNET_RX_PAGE_SIZE ; 
 scalar_t__ dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 struct device* tb_ring_dma_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_ring_rx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tbnet_free_buffers (struct tbnet_ring*) ; 

__attribute__((used)) static int tbnet_alloc_rx_buffers(struct tbnet *net, unsigned int nbuffers)
{
	struct tbnet_ring *ring = &net->rx_ring;
	int ret;

	while (nbuffers--) {
		struct device *dma_dev = tb_ring_dma_device(ring->ring);
		unsigned int index = ring->prod & (TBNET_RING_SIZE - 1);
		struct tbnet_frame *tf = &ring->frames[index];
		dma_addr_t dma_addr;

		if (tf->page)
			break;

		/* Allocate page (order > 0) so that it can hold maximum
		 * ThunderboltIP frame (4kB) and the additional room for
		 * SKB shared info required by build_skb().
		 */
		tf->page = dev_alloc_pages(TBNET_RX_PAGE_ORDER);
		if (!tf->page) {
			ret = -ENOMEM;
			goto err_free;
		}

		dma_addr = dma_map_page(dma_dev, tf->page, 0,
					TBNET_RX_PAGE_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(dma_dev, dma_addr)) {
			ret = -ENOMEM;
			goto err_free;
		}

		tf->frame.buffer_phy = dma_addr;
		tf->dev = net->dev;

		tb_ring_rx(ring->ring, &tf->frame);

		ring->prod++;
	}

	return 0;

err_free:
	tbnet_free_buffers(ring);
	return ret;
}