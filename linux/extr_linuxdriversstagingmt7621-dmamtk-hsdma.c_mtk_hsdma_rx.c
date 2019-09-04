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
struct mtk_hsdma_chan {int rx_idx; int next_sg; } ;
struct mtk_hsdam_engine {struct mtk_hsdma_chan* chan; } ;

/* Variables and functions */
 int HSDMA_DESCS_MASK ; 
 int HSDMA_NEXT_DESC (int) ; 
 int /*<<< orphan*/  HSDMA_REG_RX_CRX ; 
 int /*<<< orphan*/  HSDMA_REG_RX_DRX ; 
 int /*<<< orphan*/  mtk_hsdma_chan_done (struct mtk_hsdam_engine*,struct mtk_hsdma_chan*) ; 
 int mtk_hsdma_read (struct mtk_hsdam_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hsdma_write (struct mtk_hsdam_engine*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mtk_hsdma_rx(struct mtk_hsdam_engine *hsdma)
{
	struct mtk_hsdma_chan *chan;
	int next_idx, drx_idx, cnt;

	chan = &hsdma->chan[0];
	next_idx = HSDMA_NEXT_DESC(chan->rx_idx);
	drx_idx = mtk_hsdma_read(hsdma, HSDMA_REG_RX_DRX);

	cnt = (drx_idx - next_idx) & HSDMA_DESCS_MASK;
	if (!cnt)
		return;

	chan->next_sg += cnt;
	chan->rx_idx = (chan->rx_idx + cnt) & HSDMA_DESCS_MASK;

	/* update rx crx */
	wmb();
	mtk_hsdma_write(hsdma, HSDMA_REG_RX_CRX, chan->rx_idx);

	mtk_hsdma_chan_done(hsdma, chan);
}