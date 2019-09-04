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
struct mcfqspi {int /*<<< orphan*/  waitq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MCFQSPI_QIR_SPIF ; 
 int MCFQSPI_QIR_SPIFE ; 
 int /*<<< orphan*/  mcfqspi_wr_qir (struct mcfqspi*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mcfqspi_irq_handler(int this_irq, void *dev_id)
{
	struct mcfqspi *mcfqspi = dev_id;

	/* clear interrupt */
	mcfqspi_wr_qir(mcfqspi, MCFQSPI_QIR_SPIFE | MCFQSPI_QIR_SPIF);
	wake_up(&mcfqspi->waitq);

	return IRQ_HANDLED;
}