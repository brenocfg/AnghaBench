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
struct dwc2_hsotg_ep {int isochronous; scalar_t__ dir_in; } ;

/* Variables and functions */
 unsigned int DEV_DMA_ISOC_RX_NBYTES_LIMIT ; 
 unsigned int DEV_DMA_ISOC_TX_NBYTES_LIMIT ; 
 unsigned int DEV_DMA_NBYTES_LIMIT ; 
 unsigned int MAX_DMA_DESC_NUM_GENERIC ; 

__attribute__((used)) static unsigned int dwc2_gadget_get_chain_limit(struct dwc2_hsotg_ep *hs_ep)
{
	int is_isoc = hs_ep->isochronous;
	unsigned int maxsize;

	if (is_isoc)
		maxsize = hs_ep->dir_in ? DEV_DMA_ISOC_TX_NBYTES_LIMIT :
					   DEV_DMA_ISOC_RX_NBYTES_LIMIT;
	else
		maxsize = DEV_DMA_NBYTES_LIMIT;

	/* Above size of one descriptor was chosen, multiple it */
	maxsize *= MAX_DMA_DESC_NUM_GENERIC;

	return maxsize;
}