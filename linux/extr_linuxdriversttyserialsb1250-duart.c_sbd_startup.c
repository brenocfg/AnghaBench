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
struct uart_port {int line; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct sbd_port {int tx_stopped; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int M_DUART_IMR_IN ; 
 int M_DUART_IMR_RX ; 
 unsigned int M_DUART_RX_EN ; 
 unsigned int M_DUART_RX_IRQ_SEL_RXFULL ; 
 unsigned int M_DUART_TX_DIS ; 
 unsigned int M_DUART_TX_IRQ_SEL_TXEMPT ; 
 int /*<<< orphan*/  R_DUART_CMD ; 
 int /*<<< orphan*/  R_DUART_IMRREG (int) ; 
 int /*<<< orphan*/  R_DUART_INCHREG (int) ; 
 int /*<<< orphan*/  R_DUART_MODE_REG_1 ; 
 unsigned int V_DUART_MISC_CMD_RESET_BREAK_INT ; 
 unsigned int read_sbdchn (struct sbd_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_sbdshr (struct sbd_port*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sbd_port*) ; 
 int /*<<< orphan*/  sbd_interrupt ; 
 int /*<<< orphan*/  sbd_receive_drain (struct sbd_port*) ; 
 struct sbd_port* to_sport (struct uart_port*) ; 
 int /*<<< orphan*/  write_sbdchn (struct sbd_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  write_sbdshr (struct sbd_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbd_startup(struct uart_port *uport)
{
	struct sbd_port *sport = to_sport(uport);
	unsigned int mode1;
	int ret;

	ret = request_irq(sport->port.irq, sbd_interrupt,
			  IRQF_SHARED, "sb1250-duart", sport);
	if (ret)
		return ret;

	/* Clear the receive FIFO.  */
	sbd_receive_drain(sport);

	/* Clear the interrupt registers.  */
	write_sbdchn(sport, R_DUART_CMD, V_DUART_MISC_CMD_RESET_BREAK_INT);
	read_sbdshr(sport, R_DUART_INCHREG((uport->line) % 2));

	/* Set rx/tx interrupt to FIFO available.  */
	mode1 = read_sbdchn(sport, R_DUART_MODE_REG_1);
	mode1 &= ~(M_DUART_RX_IRQ_SEL_RXFULL | M_DUART_TX_IRQ_SEL_TXEMPT);
	write_sbdchn(sport, R_DUART_MODE_REG_1, mode1);

	/* Disable tx, enable rx.  */
	write_sbdchn(sport, R_DUART_CMD, M_DUART_TX_DIS | M_DUART_RX_EN);
	sport->tx_stopped = 1;

	/* Enable interrupts.  */
	write_sbdshr(sport, R_DUART_IMRREG((uport->line) % 2),
		     M_DUART_IMR_IN | M_DUART_IMR_RX);

	return 0;
}