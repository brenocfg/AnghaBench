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
struct mtk_hsdma_chan {scalar_t__ desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mtk_hsdam_engine {TYPE_1__ ddev; struct mtk_hsdma_chan* chan; int /*<<< orphan*/  chan_issued; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtk_hsdma_start_transfer (struct mtk_hsdam_engine*,struct mtk_hsdma_chan*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_hsdma_tx(struct mtk_hsdam_engine *hsdma)
{
	struct mtk_hsdma_chan *chan;

	if (test_and_clear_bit(0, &hsdma->chan_issued)) {
		chan = &hsdma->chan[0];
		if (chan->desc)
			mtk_hsdma_start_transfer(hsdma, chan);
		else
			dev_dbg(hsdma->ddev.dev, "chan 0 no desc to issue\n");
	}
}