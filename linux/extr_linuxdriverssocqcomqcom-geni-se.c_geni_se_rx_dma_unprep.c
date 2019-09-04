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
struct geni_wrapper {int /*<<< orphan*/  dev; } ;
struct geni_se {struct geni_wrapper* wrapper; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void geni_se_rx_dma_unprep(struct geni_se *se, dma_addr_t iova, size_t len)
{
	struct geni_wrapper *wrapper = se->wrapper;

	if (iova && !dma_mapping_error(wrapper->dev, iova))
		dma_unmap_single(wrapper->dev, iova, len, DMA_FROM_DEVICE);
}