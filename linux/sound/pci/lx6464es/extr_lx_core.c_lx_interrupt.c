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
typedef  int u32 ;
struct lx6464es {int irqsrc; TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int MASK_SYS_STATUS_CMD_DONE ; 
 int MASK_SYS_STATUS_EOBI ; 
 int MASK_SYS_STATUS_EOBO ; 
 int MASK_SYS_STATUS_ORUN ; 
 int MASK_SYS_STATUS_URUN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lx_interrupt_ack (struct lx6464es*,int*,int*,int*) ; 

irqreturn_t lx_interrupt(int irq, void *dev_id)
{
	struct lx6464es *chip = dev_id;
	int async_pending, async_escmd;
	u32 irqsrc;
	bool wake_thread = false;

	dev_dbg(chip->card->dev,
		"**************************************************\n");

	if (!lx_interrupt_ack(chip, &irqsrc, &async_pending, &async_escmd)) {
		dev_dbg(chip->card->dev, "IRQ_NONE\n");
		return IRQ_NONE; /* this device did not cause the interrupt */
	}

	if (irqsrc & MASK_SYS_STATUS_CMD_DONE)
		return IRQ_HANDLED;

	if (irqsrc & MASK_SYS_STATUS_EOBI)
		dev_dbg(chip->card->dev, "interrupt: EOBI\n");

	if (irqsrc & MASK_SYS_STATUS_EOBO)
		dev_dbg(chip->card->dev, "interrupt: EOBO\n");

	if (irqsrc & MASK_SYS_STATUS_URUN)
		dev_dbg(chip->card->dev, "interrupt: URUN\n");

	if (irqsrc & MASK_SYS_STATUS_ORUN)
		dev_dbg(chip->card->dev, "interrupt: ORUN\n");

	if (async_pending) {
		wake_thread = true;
		chip->irqsrc = irqsrc;
	}

	if (async_escmd) {
		/* backdoor for ethersound commands
		 *
		 * for now, we do not need this
		 *
		 * */

		dev_dbg(chip->card->dev, "interrupt requests escmd handling\n");
	}

	return wake_thread ? IRQ_WAKE_THREAD : IRQ_HANDLED;
}