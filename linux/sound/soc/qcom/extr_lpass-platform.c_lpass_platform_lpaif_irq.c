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
struct lpass_variant {int dummy; } ;
struct lpass_data {scalar_t__* substream; int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  LPAIF_IRQSTAT_REG (struct lpass_variant*,int /*<<< orphan*/ ) ; 
 unsigned int LPAIF_IRQ_ALL (int) ; 
 int /*<<< orphan*/  LPAIF_IRQ_PORT_HOST ; 
 int LPASS_MAX_DMA_CHANNELS ; 
 int lpass_dma_interrupt_handler (scalar_t__,struct lpass_data*,int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t lpass_platform_lpaif_irq(int irq, void *data)
{
	struct lpass_data *drvdata = data;
	struct lpass_variant *v = drvdata->variant;
	unsigned int irqs;
	int rv, chan;

	rv = regmap_read(drvdata->lpaif_map,
			LPAIF_IRQSTAT_REG(v, LPAIF_IRQ_PORT_HOST), &irqs);
	if (rv) {
		pr_err("error reading from irqstat reg: %d\n", rv);
		return IRQ_NONE;
	}

	/* Handle per channel interrupts */
	for (chan = 0; chan < LPASS_MAX_DMA_CHANNELS; chan++) {
		if (irqs & LPAIF_IRQ_ALL(chan) && drvdata->substream[chan]) {
			rv = lpass_dma_interrupt_handler(
						drvdata->substream[chan],
						drvdata, chan, irqs);
			if (rv != IRQ_HANDLED)
				return rv;
		}
	}

	return IRQ_HANDLED;
}