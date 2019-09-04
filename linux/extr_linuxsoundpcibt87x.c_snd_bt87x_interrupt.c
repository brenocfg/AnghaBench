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
struct snd_bt87x {unsigned int interrupt_mask; int reg_control; int current_line; int lines; int /*<<< orphan*/  substream; TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTL_ACAP_EN ; 
 unsigned int ERROR_INTERRUPTS ; 
 unsigned int INT_FBUS ; 
 unsigned int INT_FTRGT ; 
 unsigned int INT_OCERR ; 
 unsigned int INT_PABORT ; 
 unsigned int INT_PPERR ; 
 unsigned int INT_RIPERR ; 
 unsigned int INT_RISCI ; 
 unsigned int INT_RISCS_SHIFT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REG_INT_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  snd_bt87x_pci_error (struct snd_bt87x*,unsigned int) ; 
 unsigned int snd_bt87x_readl (struct snd_bt87x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_bt87x_writel (struct snd_bt87x*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snd_bt87x_interrupt(int irq, void *dev_id)
{
	struct snd_bt87x *chip = dev_id;
	unsigned int status, irq_status;

	status = snd_bt87x_readl(chip, REG_INT_STAT);
	irq_status = status & chip->interrupt_mask;
	if (!irq_status)
		return IRQ_NONE;
	snd_bt87x_writel(chip, REG_INT_STAT, irq_status);

	if (irq_status & ERROR_INTERRUPTS) {
		if (irq_status & (INT_FBUS | INT_FTRGT))
			dev_warn(chip->card->dev,
				 "FIFO overrun, status %#08x\n", status);
		if (irq_status & INT_OCERR)
			dev_err(chip->card->dev,
				"internal RISC error, status %#08x\n", status);
		if (irq_status & (INT_PPERR | INT_RIPERR | INT_PABORT))
			snd_bt87x_pci_error(chip, irq_status);
	}
	if ((irq_status & INT_RISCI) && (chip->reg_control & CTL_ACAP_EN)) {
		int current_block, irq_block;

		/* assume that exactly one line has been recorded */
		chip->current_line = (chip->current_line + 1) % chip->lines;
		/* but check if some interrupts have been skipped */
		current_block = chip->current_line * 16 / chip->lines;
		irq_block = status >> INT_RISCS_SHIFT;
		if (current_block != irq_block)
			chip->current_line = (irq_block * chip->lines + 15) / 16;

		snd_pcm_period_elapsed(chip->substream);
	}
	return IRQ_HANDLED;
}