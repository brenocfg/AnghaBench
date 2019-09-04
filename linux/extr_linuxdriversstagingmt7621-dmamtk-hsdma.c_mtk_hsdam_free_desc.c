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
struct mtk_hsdma_chan {int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  desc_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mtk_hsdam_engine {TYPE_1__ ddev; } ;

/* Variables and functions */
 int HSDMA_DESCS_NUM ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hsdam_free_desc(struct mtk_hsdam_engine *hsdma,
				struct mtk_hsdma_chan *chan)
{
	if (chan->tx_ring) {
		dma_free_coherent(hsdma->ddev.dev,
				2 * HSDMA_DESCS_NUM * sizeof(*chan->tx_ring),
				chan->tx_ring, chan->desc_addr);
		chan->tx_ring = NULL;
		chan->rx_ring = NULL;
	}
}