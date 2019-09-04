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
struct uart_port {scalar_t__ uartclk; int /*<<< orphan*/  irq; scalar_t__ mapbase; int /*<<< orphan*/  iobase; int /*<<< orphan*/ * dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; int /*<<< orphan*/  membase; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int) ; 
 struct uart_port* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int serial_txx9_register_port (struct uart_port*) ; 

__attribute__((used)) static int serial_txx9_probe(struct platform_device *dev)
{
	struct uart_port *p = dev_get_platdata(&dev->dev);
	struct uart_port port;
	int ret, i;

	memset(&port, 0, sizeof(struct uart_port));
	for (i = 0; p && p->uartclk != 0; p++, i++) {
		port.iobase	= p->iobase;
		port.membase	= p->membase;
		port.irq	= p->irq;
		port.uartclk	= p->uartclk;
		port.iotype	= p->iotype;
		port.flags	= p->flags;
		port.mapbase	= p->mapbase;
		port.dev	= &dev->dev;
		ret = serial_txx9_register_port(&port);
		if (ret < 0) {
			dev_err(&dev->dev, "unable to register port at index %d "
				"(IO%lx MEM%llx IRQ%d): %d\n", i,
				p->iobase, (unsigned long long)p->mapbase,
				p->irq, ret);
		}
	}
	return 0;
}