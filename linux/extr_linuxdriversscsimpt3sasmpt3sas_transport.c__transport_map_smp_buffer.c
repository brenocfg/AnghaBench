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
struct device {int dummy; } ;
struct bsg_buffer {int sg_cnt; size_t payload_len; int /*<<< orphan*/  sg_list; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 size_t sg_dma_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_transport_map_smp_buffer(struct device *dev, struct bsg_buffer *buf,
		dma_addr_t *dma_addr, size_t *dma_len, void **p)
{
	/* Check if the request is split across multiple segments */
	if (buf->sg_cnt > 1) {
		*p = dma_alloc_coherent(dev, buf->payload_len, dma_addr,
				GFP_KERNEL);
		if (!*p)
			return -ENOMEM;
		*dma_len = buf->payload_len;
	} else {
		if (!dma_map_sg(dev, buf->sg_list, 1, DMA_BIDIRECTIONAL))
			return -ENOMEM;
		*dma_addr = sg_dma_address(buf->sg_list);
		*dma_len = sg_dma_len(buf->sg_list);
		*p = NULL;
	}

	return 0;
}