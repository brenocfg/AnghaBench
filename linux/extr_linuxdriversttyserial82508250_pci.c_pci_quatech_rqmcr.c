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
typedef  int u8 ;
struct TYPE_2__ {unsigned long iobase; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ UART_LCR ; 
 scalar_t__ UART_MCR ; 
 scalar_t__ UART_SCR ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int pci_quatech_rqmcr(struct uart_8250_port *port)
{
	unsigned long base = port->port.iobase;
	u8 LCR, val, qmcr;

	LCR = inb(base + UART_LCR);
	outb(0xBF, base + UART_LCR);
	val = inb(base + UART_SCR);
	outb(val | 0x10, base + UART_SCR);
	qmcr = inb(base + UART_MCR);
	outb(val, base + UART_SCR);
	outb(LCR, base + UART_LCR);

	return qmcr;
}