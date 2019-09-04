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
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct vring_tx_desc {TYPE_1__ dma; } ;
union wil_tx_desc {struct vring_tx_desc legacy; } ;
typedef  int /*<<< orphan*/  u16 ;
struct wil_ctx {int mapped_as; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_desc_addr (int /*<<< orphan*/ *) ; 
#define  wil_mapped_as_page 129 
#define  wil_mapped_as_single 128 

__attribute__((used)) static void wil_txdesc_unmap(struct device *dev, union wil_tx_desc *desc,
			     struct wil_ctx *ctx)
{
	struct vring_tx_desc *d = &desc->legacy;
	dma_addr_t pa = wil_desc_addr(&d->dma.addr);
	u16 dmalen = le16_to_cpu(d->dma.length);

	switch (ctx->mapped_as) {
	case wil_mapped_as_single:
		dma_unmap_single(dev, pa, dmalen, DMA_TO_DEVICE);
		break;
	case wil_mapped_as_page:
		dma_unmap_page(dev, pa, dmalen, DMA_TO_DEVICE);
		break;
	default:
		break;
	}
}