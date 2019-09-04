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
struct lpuart_port {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UARTBAUD ; 
 unsigned long UARTBAUD_TDMAE ; 
 int /*<<< orphan*/  UARTSTAT ; 
 unsigned long UARTSTAT_RDRF ; 
 unsigned long UARTSTAT_TDRE ; 
 int /*<<< orphan*/  UARTWATER ; 
 unsigned long UARTWATER_RXCNT_OFF ; 
 unsigned long lpuart32_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_rxint (int,void*) ; 
 int /*<<< orphan*/  lpuart32_write (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_txint (int,void*) ; 

__attribute__((used)) static irqreturn_t lpuart32_int(int irq, void *dev_id)
{
	struct lpuart_port *sport = dev_id;
	unsigned long sts, rxcount;

	sts = lpuart32_read(&sport->port, UARTSTAT);
	rxcount = lpuart32_read(&sport->port, UARTWATER);
	rxcount = rxcount >> UARTWATER_RXCNT_OFF;

	if (sts & UARTSTAT_RDRF || rxcount > 0)
		lpuart32_rxint(irq, dev_id);

	if ((sts & UARTSTAT_TDRE) &&
		!(lpuart32_read(&sport->port, UARTBAUD) & UARTBAUD_TDMAE))
		lpuart_txint(irq, dev_id);

	lpuart32_write(&sport->port, sts, UARTSTAT);
	return IRQ_HANDLED;
}