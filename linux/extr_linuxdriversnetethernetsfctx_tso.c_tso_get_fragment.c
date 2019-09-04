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
struct tso_state {int /*<<< orphan*/  unmap_addr; int /*<<< orphan*/  dma_addr; void* in_len; void* unmap_len; } ;
struct efx_nic {TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* skb_frag_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tso_get_fragment(struct tso_state *st, struct efx_nic *efx,
			    skb_frag_t *frag)
{
	st->unmap_addr = skb_frag_dma_map(&efx->pci_dev->dev, frag, 0,
					  skb_frag_size(frag), DMA_TO_DEVICE);
	if (likely(!dma_mapping_error(&efx->pci_dev->dev, st->unmap_addr))) {
		st->unmap_len = skb_frag_size(frag);
		st->in_len = skb_frag_size(frag);
		st->dma_addr = st->unmap_addr;
		return 0;
	}
	return -ENOMEM;
}