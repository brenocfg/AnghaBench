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
struct uart_port {int /*<<< orphan*/  mapbase; } ;
struct sirfsoc_uart_port {TYPE_1__* uart_reg; } ;
struct sirfsoc_uart_param {int /*<<< orphan*/  port_name; } ;
struct TYPE_2__ {struct sirfsoc_uart_param uart_param; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SIRFUART_MAP_SIZE ; 
 void* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 

__attribute__((used)) static int sirfsoc_uart_request_port(struct uart_port *port)
{
	struct sirfsoc_uart_port *sirfport = to_sirfport(port);
	struct sirfsoc_uart_param *uart_param = &sirfport->uart_reg->uart_param;
	void *ret;
	ret = request_mem_region(port->mapbase,
		SIRFUART_MAP_SIZE, uart_param->port_name);
	return ret ? 0 : -EBUSY;
}