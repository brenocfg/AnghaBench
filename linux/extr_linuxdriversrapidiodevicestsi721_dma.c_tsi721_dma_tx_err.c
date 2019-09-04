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
struct dma_async_tx_descriptor {void* callback_param; int /*<<< orphan*/  (* callback ) (void*) ;} ;
struct tsi721_tx_desc {int /*<<< orphan*/  desc_node; struct dma_async_tx_descriptor txd; } ;
struct tsi721_bdma_chan {int /*<<< orphan*/  free_list; } ;
typedef  int /*<<< orphan*/  (* dma_async_tx_callback ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tsi721_dma_tx_err(struct tsi721_bdma_chan *bdma_chan,
			      struct tsi721_tx_desc *desc)
{
	struct dma_async_tx_descriptor *txd = &desc->txd;
	dma_async_tx_callback callback = txd->callback;
	void *param = txd->callback_param;

	list_move(&desc->desc_node, &bdma_chan->free_list);

	if (callback)
		callback(param);
}