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
typedef  int u32 ;
struct uart_port {scalar_t__ membase; } ;
struct men_z135_port {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int MEN_Z135_ALL_IRQS ; 
 scalar_t__ MEN_Z135_CONF_REG ; 
 int MEN_Z135_IER_TXCIEN ; 
 scalar_t__ MEN_Z135_TIMEOUT ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int men_z135_request_irq (struct men_z135_port*) ; 
 int rx_timeout ; 
 int rxlvl ; 
 struct men_z135_port* to_men_z135 (struct uart_port*) ; 
 int txlvl ; 

__attribute__((used)) static int men_z135_startup(struct uart_port *port)
{
	struct men_z135_port *uart = to_men_z135(port);
	int err;
	u32 conf_reg = 0;

	err = men_z135_request_irq(uart);
	if (err)
		return -ENODEV;

	conf_reg = ioread32(port->membase + MEN_Z135_CONF_REG);

	/* Activate all but TX space available IRQ */
	conf_reg |= MEN_Z135_ALL_IRQS & ~MEN_Z135_IER_TXCIEN;
	conf_reg &= ~(0xff << 16);
	conf_reg |= (txlvl << 16);
	conf_reg |= (rxlvl << 20);

	iowrite32(conf_reg, port->membase + MEN_Z135_CONF_REG);

	if (rx_timeout)
		iowrite32(rx_timeout, port->membase + MEN_Z135_TIMEOUT);

	return 0;
}