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
struct udc {int /*<<< orphan*/  data_requests; int /*<<< orphan*/  stp_requests; TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_stp_dma; int /*<<< orphan*/  td_stp; int /*<<< orphan*/  td_phys; int /*<<< orphan*/  td; } ;

/* Variables and functions */
 size_t UDC_EP0OUT_IX ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void free_dma_pools(struct udc *dev)
{
	dma_pool_free(dev->stp_requests, dev->ep[UDC_EP0OUT_IX].td,
		      dev->ep[UDC_EP0OUT_IX].td_phys);
	dma_pool_free(dev->stp_requests, dev->ep[UDC_EP0OUT_IX].td_stp,
		      dev->ep[UDC_EP0OUT_IX].td_stp_dma);
	dma_pool_destroy(dev->stp_requests);
	dma_pool_destroy(dev->data_requests);
}