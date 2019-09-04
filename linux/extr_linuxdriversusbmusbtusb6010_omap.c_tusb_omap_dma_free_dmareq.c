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
struct tusb_omap_dma_ch {TYPE_1__* dma_data; int /*<<< orphan*/  tbase; } ;
struct TYPE_2__ {int dmareq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUSB_DMA_EP_MAP ; 
 int musb_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void tusb_omap_dma_free_dmareq(struct tusb_omap_dma_ch *chdat)
{
	u32 reg;

	if (!chdat || !chdat->dma_data || chdat->dma_data->dmareq < 0)
		return;

	reg = musb_readl(chdat->tbase, TUSB_DMA_EP_MAP);
	reg &= ~(0x1f << (chdat->dma_data->dmareq * 5));
	musb_writel(chdat->tbase, TUSB_DMA_EP_MAP, reg);

	chdat->dma_data = NULL;
}