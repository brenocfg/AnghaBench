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
struct ag71xx_ring {struct ag71xx_buf* buf; } ;
struct ag71xx_desc {int data; } ;
struct ag71xx_buf {scalar_t__ dma_addr; void* rx_buf; } ;
struct ag71xx {int /*<<< orphan*/  rx_buf_size; TYPE_1__* pdev; struct ag71xx_ring rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int ag71xx_buffer_size (struct ag71xx*) ; 
 struct ag71xx_desc* ag71xx_ring_desc (struct ag71xx_ring*,int) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ag71xx_fill_rx_buf(struct ag71xx *ag, struct ag71xx_buf *buf,
			       int offset,
			       void *(*alloc)(unsigned int size))
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	struct ag71xx_desc *desc = ag71xx_ring_desc(ring, buf - &ring->buf[0]);
	void *data;

	data = alloc(ag71xx_buffer_size(ag));
	if (!data)
		return false;

	buf->rx_buf = data;
	buf->dma_addr = dma_map_single(&ag->pdev->dev, data, ag->rx_buf_size,
				       DMA_FROM_DEVICE);
	desc->data = (u32) buf->dma_addr + offset;
	return true;
}