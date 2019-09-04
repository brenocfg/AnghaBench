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
struct uart_port {scalar_t__ type; scalar_t__ irq; } ;
struct serial_struct {scalar_t__ irq; int baud_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PORT_MESON ; 

__attribute__((used)) static int meson_uart_verify_port(struct uart_port *port,
				  struct serial_struct *ser)
{
	int ret = 0;

	if (port->type != PORT_MESON)
		ret = -EINVAL;
	if (port->irq != ser->irq)
		ret = -EINVAL;
	if (ser->baud_base < 9600)
		ret = -EINVAL;
	return ret;
}