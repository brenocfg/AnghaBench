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
typedef  int uint32_t ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_otg_dev_dma_desc_t ;
typedef  int /*<<< orphan*/  dwc_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DWC_DMA_ALLOC_ATOMIC (struct device*,int,int /*<<< orphan*/ *) ; 

dwc_otg_dev_dma_desc_t *dwc_otg_ep_alloc_desc_chain(struct device *dev,
						    dwc_dma_t * dma_desc_addr,
						    uint32_t count)
{
	return DWC_DMA_ALLOC_ATOMIC(dev, count * sizeof(dwc_otg_dev_dma_desc_t),
							dma_desc_addr);
}