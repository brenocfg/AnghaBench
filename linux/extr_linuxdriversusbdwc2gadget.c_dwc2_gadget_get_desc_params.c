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
struct TYPE_2__ {int maxpacket; } ;
struct dwc2_hsotg_ep {int dir_in; scalar_t__ isochronous; int /*<<< orphan*/  index; TYPE_1__ ep; } ;

/* Variables and functions */
 int DEV_DMA_ISOC_RX_NBYTES_LIMIT ; 
 int DEV_DMA_ISOC_RX_NBYTES_MASK ; 
 int DEV_DMA_ISOC_TX_NBYTES_LIMIT ; 
 int DEV_DMA_ISOC_TX_NBYTES_MASK ; 
 int DEV_DMA_NBYTES_LIMIT ; 
 int DEV_DMA_NBYTES_MASK ; 

__attribute__((used)) static u32 dwc2_gadget_get_desc_params(struct dwc2_hsotg_ep *hs_ep, u32 *mask)
{
	u32 mps = hs_ep->ep.maxpacket;
	int dir_in = hs_ep->dir_in;
	u32 desc_size = 0;

	if (!hs_ep->index && !dir_in) {
		desc_size = mps;
		*mask = DEV_DMA_NBYTES_MASK;
	} else if (hs_ep->isochronous) {
		if (dir_in) {
			desc_size = DEV_DMA_ISOC_TX_NBYTES_LIMIT;
			*mask = DEV_DMA_ISOC_TX_NBYTES_MASK;
		} else {
			desc_size = DEV_DMA_ISOC_RX_NBYTES_LIMIT;
			*mask = DEV_DMA_ISOC_RX_NBYTES_MASK;
		}
	} else {
		desc_size = DEV_DMA_NBYTES_LIMIT;
		*mask = DEV_DMA_NBYTES_MASK;

		/* Round down desc_size to be mps multiple */
		desc_size -= desc_size % mps;
	}

	return desc_size;
}