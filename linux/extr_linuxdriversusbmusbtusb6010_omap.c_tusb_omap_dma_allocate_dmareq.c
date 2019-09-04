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
struct tusb_omap_dma_ch {int epnum; TYPE_1__* tusb_dma; int /*<<< orphan*/ * dma_data; int /*<<< orphan*/  tbase; scalar_t__ tx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dma_pool; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MAX_DMAREQ ; 
 int /*<<< orphan*/  TUSB_DMA_EP_MAP ; 
 int musb_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int tusb_omap_dma_allocate_dmareq(struct tusb_omap_dma_ch *chdat)
{
	u32		reg = musb_readl(chdat->tbase, TUSB_DMA_EP_MAP);
	int		i, dmareq_nr = -1;

	for (i = 0; i < MAX_DMAREQ; i++) {
		int cur = (reg & (0xf << (i * 5))) >> (i * 5);
		if (cur == 0) {
			dmareq_nr = i;
			break;
		}
	}

	if (dmareq_nr == -1)
		return -EAGAIN;

	reg |= (chdat->epnum << (dmareq_nr * 5));
	if (chdat->tx)
		reg |= ((1 << 4) << (dmareq_nr * 5));
	musb_writel(chdat->tbase, TUSB_DMA_EP_MAP, reg);

	chdat->dma_data = &chdat->tusb_dma->dma_pool[dmareq_nr];

	return 0;
}