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
struct pic32_spi {scalar_t__ tx_end; scalar_t__ tx; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  (* tx_fifo ) (struct pic32_spi*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pic32_spi*) ; 

__attribute__((used)) static irqreturn_t pic32_spi_tx_irq(int irq, void *dev_id)
{
	struct pic32_spi *pic32s = dev_id;

	pic32s->tx_fifo(pic32s);

	/* tx complete? disable tx interrupt */
	if (pic32s->tx_end == pic32s->tx)
		disable_irq_nosync(pic32s->tx_irq);

	return IRQ_HANDLED;
}