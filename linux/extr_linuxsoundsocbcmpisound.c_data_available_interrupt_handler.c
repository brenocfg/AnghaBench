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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TASK_PROCESS ; 
 int /*<<< orphan*/  data_available ; 
 int gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pisnd_schedule_process (int /*<<< orphan*/ ) ; 
 scalar_t__ pisnd_spi_has_more () ; 
 int /*<<< orphan*/  printd (char*) ; 

__attribute__((used)) static irqreturn_t data_available_interrupt_handler(int irq, void *dev_id)
{
	if (irq == gpiod_to_irq(data_available) && pisnd_spi_has_more()) {
		printd("schedule from irq\n");
		pisnd_schedule_process(TASK_PROCESS);
	}

	return IRQ_HANDLED;
}