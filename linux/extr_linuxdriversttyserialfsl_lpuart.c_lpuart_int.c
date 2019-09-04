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
struct TYPE_2__ {scalar_t__ membase; } ;
struct lpuart_port {TYPE_1__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ UARTSR1 ; 
 unsigned char UARTSR1_RDRF ; 
 unsigned char UARTSR1_TDRE ; 
 int /*<<< orphan*/  lpuart_rxint (int,void*) ; 
 int /*<<< orphan*/  lpuart_txint (int,void*) ; 
 unsigned char readb (scalar_t__) ; 

__attribute__((used)) static irqreturn_t lpuart_int(int irq, void *dev_id)
{
	struct lpuart_port *sport = dev_id;
	unsigned char sts;

	sts = readb(sport->port.membase + UARTSR1);

	if (sts & UARTSR1_RDRF)
		lpuart_rxint(irq, dev_id);

	if (sts & UARTSR1_TDRE)
		lpuart_txint(irq, dev_id);

	return IRQ_HANDLED;
}