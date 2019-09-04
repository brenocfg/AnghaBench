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
struct serial_rs485 {int flags; } ;
struct uart_port {struct serial_rs485 rs485; scalar_t__ membase; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char MCFUART_MR2_TXRTS ; 
 scalar_t__ MCFUART_UMR ; 
 int SER_RS485_ENABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int mcf_config_rs485(struct uart_port *port, struct serial_rs485 *rs485)
{
	unsigned char mr1, mr2;

	/* Get mode registers */
	mr1 = readb(port->membase + MCFUART_UMR);
	mr2 = readb(port->membase + MCFUART_UMR);
	if (rs485->flags & SER_RS485_ENABLED) {
		dev_dbg(port->dev, "Setting UART to RS485\n");
		/* Automatically negate RTS after TX completes */
		mr2 |= MCFUART_MR2_TXRTS;
	} else {
		dev_dbg(port->dev, "Setting UART to RS232\n");
		mr2 &= ~MCFUART_MR2_TXRTS;
	}
	writeb(mr1, port->membase + MCFUART_UMR);
	writeb(mr2, port->membase + MCFUART_UMR);
	port->rs485 = *rs485;

	return 0;
}