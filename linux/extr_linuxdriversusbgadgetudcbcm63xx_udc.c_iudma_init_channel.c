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
struct iudma_ch_cfg {unsigned int n_bds; size_t ep_num; } ;
struct iudma_ch {size_t ep_num; unsigned int ch_idx; int is_tx; int enabled; unsigned int n_bds; int /*<<< orphan*/ * bd_ring; int /*<<< orphan*/ * end_bd; int /*<<< orphan*/  bd_ring_dma; struct bcm63xx_udc* udc; struct bcm63xx_ep* bep; } ;
struct bcm_enet_desc {int dummy; } ;
struct bcm63xx_udc {int /*<<< orphan*/  dev; struct bcm63xx_ep* bep; struct iudma_ch* iudma; } ;
struct bcm63xx_ep {int /*<<< orphan*/  queue; struct iudma_ch* iudma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmam_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iudma_ch_cfg* iudma_defaults ; 

__attribute__((used)) static int iudma_init_channel(struct bcm63xx_udc *udc, unsigned int ch_idx)
{
	struct iudma_ch *iudma = &udc->iudma[ch_idx];
	const struct iudma_ch_cfg *cfg = &iudma_defaults[ch_idx];
	unsigned int n_bds = cfg->n_bds;
	struct bcm63xx_ep *bep = NULL;

	iudma->ep_num = cfg->ep_num;
	iudma->ch_idx = ch_idx;
	iudma->is_tx = !!(ch_idx & 0x01);
	if (iudma->ep_num >= 0) {
		bep = &udc->bep[iudma->ep_num];
		bep->iudma = iudma;
		INIT_LIST_HEAD(&bep->queue);
	}

	iudma->bep = bep;
	iudma->udc = udc;

	/* ep0 is always active; others are controlled by the gadget driver */
	if (iudma->ep_num <= 0)
		iudma->enabled = true;

	iudma->n_bds = n_bds;
	iudma->bd_ring = dmam_alloc_coherent(udc->dev,
		n_bds * sizeof(struct bcm_enet_desc),
		&iudma->bd_ring_dma, GFP_KERNEL);
	if (!iudma->bd_ring)
		return -ENOMEM;
	iudma->end_bd = &iudma->bd_ring[n_bds - 1];

	return 0;
}