#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_hsdma_chan {TYPE_2__* tx_ring; TYPE_2__* rx_ring; int /*<<< orphan*/  desc_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mtk_hsdam_engine {TYPE_1__ ddev; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int HSDMA_DESCS_NUM ; 
 int HSDMA_DESC_DONE ; 
 int HSDMA_DESC_LS0 ; 
 int __GFP_ZERO ; 
 TYPE_2__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtk_hsdam_alloc_desc(struct mtk_hsdam_engine *hsdma,
				struct mtk_hsdma_chan *chan)
{
	int i;

	chan->tx_ring = dma_alloc_coherent(hsdma->ddev.dev,
			2 * HSDMA_DESCS_NUM * sizeof(*chan->tx_ring),
			&chan->desc_addr, GFP_ATOMIC | __GFP_ZERO);
	if (!chan->tx_ring)
		goto no_mem;

	chan->rx_ring = &chan->tx_ring[HSDMA_DESCS_NUM];

	/* init tx ring value */
	for (i = 0; i < HSDMA_DESCS_NUM; i++)
		chan->tx_ring[i].flags = HSDMA_DESC_LS0 | HSDMA_DESC_DONE;

	return 0;
no_mem:
	return -ENOMEM;
}