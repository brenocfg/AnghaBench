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
struct uart_port {int regshift; int iotype; unsigned int (* serial_in ) (struct uart_port*,int) ;int /*<<< orphan*/  iobase; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
#define  UPIO_AU 133 
#define  UPIO_MEM 132 
#define  UPIO_MEM16 131 
#define  UPIO_MEM32 130 
#define  UPIO_MEM32BE 129 
#define  UPIO_PORT 128 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 unsigned int ioread32be (int /*<<< orphan*/ ) ; 
 unsigned int readb (int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 unsigned int readw (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct uart_port*,int) ; 

__attribute__((used)) static unsigned int serial8250_early_in(struct uart_port *port, int offset)
{
	int reg_offset = offset;
	offset <<= port->regshift;

	switch (port->iotype) {
	case UPIO_MEM:
		return readb(port->membase + offset);
	case UPIO_MEM16:
		return readw(port->membase + offset);
	case UPIO_MEM32:
		return readl(port->membase + offset);
	case UPIO_MEM32BE:
		return ioread32be(port->membase + offset);
	case UPIO_PORT:
		return inb(port->iobase + offset);
	case UPIO_AU:
		return port->serial_in(port, reg_offset);
	default:
		return 0;
	}
}