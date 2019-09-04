#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uart ;
struct TYPE_3__ {unsigned int iobase; int irq; int flags; int uartclk; int /*<<< orphan*/ * dev; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_info {int* line; size_t ndev; TYPE_2__* quirk; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* setup ) (struct pcmcia_device*,struct uart_8250_port*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_BUGGY_UART ; 
 int UPF_SHARE_IRQ ; 
 int UPF_SKIP_TEST ; 
 scalar_t__ buggy_uart ; 
 int /*<<< orphan*/  memset (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,int) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_device*,struct uart_8250_port*) ; 

__attribute__((used)) static int setup_serial(struct pcmcia_device *handle, struct serial_info *info,
			unsigned int iobase, int irq)
{
	struct uart_8250_port uart;
	int line;

	memset(&uart, 0, sizeof(uart));
	uart.port.iobase = iobase;
	uart.port.irq = irq;
	uart.port.flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_SHARE_IRQ;
	uart.port.uartclk = 1843200;
	uart.port.dev = &handle->dev;
	if (buggy_uart)
		uart.port.flags |= UPF_BUGGY_UART;

	if (info->quirk && info->quirk->setup)
		info->quirk->setup(handle, &uart);

	line = serial8250_register_8250_port(&uart);
	if (line < 0) {
		pr_err("serial_cs: serial8250_register_8250_port() at 0x%04lx, irq %d failed\n",
							(unsigned long)iobase, irq);
		return -EINVAL;
	}

	info->line[info->ndev] = line;
	info->ndev++;

	return 0;
}