#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stm32_spdifrx_data {int /*<<< orphan*/  ctrl_chan; TYPE_2__* desc; TYPE_1__* dmab; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_5__ {struct stm32_spdifrx_data* callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPDIFRX_CSR_BUF_LENGTH ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 TYPE_2__* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_2__*) ; 
 int /*<<< orphan*/  stm32_spdifrx_dma_complete ; 

__attribute__((used)) static int stm32_spdifrx_dma_ctrl_start(struct stm32_spdifrx_data *spdifrx)
{
	dma_cookie_t cookie;
	int err;

	spdifrx->desc = dmaengine_prep_slave_single(spdifrx->ctrl_chan,
						    spdifrx->dmab->addr,
						    SPDIFRX_CSR_BUF_LENGTH,
						    DMA_DEV_TO_MEM,
						    DMA_CTRL_ACK);
	if (!spdifrx->desc)
		return -EINVAL;

	spdifrx->desc->callback = stm32_spdifrx_dma_complete;
	spdifrx->desc->callback_param = spdifrx;
	cookie = dmaengine_submit(spdifrx->desc);
	err = dma_submit_error(cookie);
	if (err)
		return -EINVAL;

	dma_async_issue_pending(spdifrx->ctrl_chan);

	return 0;
}