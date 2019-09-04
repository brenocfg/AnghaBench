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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_submit; } ;
struct tsi721_tx_desc {int /*<<< orphan*/  desc_node; TYPE_2__ txd; } ;
struct tsi721_bdma_chan {int active; int /*<<< orphan*/  free_list; struct tsi721_tx_desc* tx_desc; int /*<<< orphan*/  id; scalar_t__ bd_base; } ;
struct dma_chan {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA ; 
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_2__*,struct dma_chan*) ; 
 int /*<<< orphan*/  dma_cookie_init (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_desc_per_channel ; 
 int dma_txqueue_sz ; 
 struct tsi721_tx_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tsi721_bdma_chan* to_tsi721_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  tsi721_bdma_ch_free (struct tsi721_bdma_chan*) ; 
 scalar_t__ tsi721_bdma_ch_init (struct tsi721_bdma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi721_bdma_interrupt_enable (struct tsi721_bdma_chan*,int) ; 
 int /*<<< orphan*/  tsi721_tx_submit ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsi721_alloc_chan_resources(struct dma_chan *dchan)
{
	struct tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	struct tsi721_tx_desc *desc;
	int i;

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	if (bdma_chan->bd_base)
		return dma_txqueue_sz;

	/* Initialize BDMA channel */
	if (tsi721_bdma_ch_init(bdma_chan, dma_desc_per_channel)) {
		tsi_err(&dchan->dev->device, "Unable to initialize DMAC%d",
			bdma_chan->id);
		return -ENODEV;
	}

	/* Allocate queue of transaction descriptors */
	desc = kcalloc(dma_txqueue_sz, sizeof(struct tsi721_tx_desc),
			GFP_ATOMIC);
	if (!desc) {
		tsi721_bdma_ch_free(bdma_chan);
		return -ENOMEM;
	}

	bdma_chan->tx_desc = desc;

	for (i = 0; i < dma_txqueue_sz; i++) {
		dma_async_tx_descriptor_init(&desc[i].txd, dchan);
		desc[i].txd.tx_submit = tsi721_tx_submit;
		desc[i].txd.flags = DMA_CTRL_ACK;
		list_add(&desc[i].desc_node, &bdma_chan->free_list);
	}

	dma_cookie_init(dchan);

	bdma_chan->active = true;
	tsi721_bdma_interrupt_enable(bdma_chan, 1);

	return dma_txqueue_sz;
}