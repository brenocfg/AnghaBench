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
struct uart_port {TYPE_1__* state; } ;
struct circ_buf {int dummy; } ;
struct TYPE_2__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  stm32_transmit_chars (struct uart_port*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 

__attribute__((used)) static void stm32_start_tx(struct uart_port *port)
{
	struct circ_buf *xmit = &port->state->xmit;

	if (uart_circ_empty(xmit))
		return;

	stm32_transmit_chars(port);
}