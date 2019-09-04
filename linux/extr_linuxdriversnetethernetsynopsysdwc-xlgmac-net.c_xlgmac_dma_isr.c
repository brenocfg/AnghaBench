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
struct xlgmac_channel {int /*<<< orphan*/  napi; int /*<<< orphan*/  dma_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t xlgmac_dma_isr(int irq, void *data)
{
	struct xlgmac_channel *channel = data;

	/* Per channel DMA interrupts are enabled, so we use the per
	 * channel napi structure and not the private data napi structure
	 */
	if (napi_schedule_prep(&channel->napi)) {
		/* Disable Tx and Rx interrupts */
		disable_irq_nosync(channel->dma_irq);

		/* Turn on polling */
		__napi_schedule_irqoff(&channel->napi);
	}

	return IRQ_HANDLED;
}