#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* pbus; } ;
struct TYPE_12__ {int /*<<< orphan*/  substream; TYPE_5__ pbus; } ;
struct TYPE_8__ {TYPE_1__* pbus; } ;
struct TYPE_9__ {int /*<<< orphan*/  substream; TYPE_2__ pbus; } ;
struct snd_hal2 {TYPE_6__ adc; TYPE_3__ dac; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_10__ {int pbdma_ctrl; } ;
struct TYPE_7__ {int pbdma_ctrl; } ;

/* Variables and functions */
 int HPC3_PDMACTRL_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hal2_interrupt(int irq, void *dev_id)
{
	struct snd_hal2 *hal2 = dev_id;
	irqreturn_t ret = IRQ_NONE;

	/* decide what caused this interrupt */
	if (hal2->dac.pbus.pbus->pbdma_ctrl & HPC3_PDMACTRL_INT) {
		snd_pcm_period_elapsed(hal2->dac.substream);
		ret = IRQ_HANDLED;
	}
	if (hal2->adc.pbus.pbus->pbdma_ctrl & HPC3_PDMACTRL_INT) {
		snd_pcm_period_elapsed(hal2->adc.substream);
		ret = IRQ_HANDLED;
	}
	return ret;
}