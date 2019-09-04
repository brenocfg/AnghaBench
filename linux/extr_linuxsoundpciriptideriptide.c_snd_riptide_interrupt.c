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
struct snd_riptide {TYPE_1__* rmidi; int /*<<< orphan*/  handled_irqs; int /*<<< orphan*/  riptide_tq; int /*<<< orphan*/  received_irqs; struct cmdif* cif; } ;
struct cmdif {int /*<<< orphan*/  hwport; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ IS_EOBIRQ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_EOCIRQ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_EOSIRQ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MPUIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_AIACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
snd_riptide_interrupt(int irq, void *dev_id)
{
	struct snd_riptide *chip = dev_id;
	struct cmdif *cif = chip->cif;

	if (cif) {
		chip->received_irqs++;
		if (IS_EOBIRQ(cif->hwport) || IS_EOSIRQ(cif->hwport) ||
		    IS_EOCIRQ(cif->hwport)) {
			chip->handled_irqs++;
			tasklet_schedule(&chip->riptide_tq);
		}
		if (chip->rmidi && IS_MPUIRQ(cif->hwport)) {
			chip->handled_irqs++;
			snd_mpu401_uart_interrupt(irq,
						  chip->rmidi->private_data);
		}
		SET_AIACK(cif->hwport);
	}
	return IRQ_HANDLED;
}