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
struct uart_port {int line; int /*<<< orphan*/  dev; } ;
struct sccnxp_port {int imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCCNXP_IMR_REG ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_write (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sccnxp_enable_irq(struct uart_port *port, int mask)
{
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	s->imr |= mask << (port->line * 4);
	sccnxp_write(port, SCCNXP_IMR_REG, s->imr);
}