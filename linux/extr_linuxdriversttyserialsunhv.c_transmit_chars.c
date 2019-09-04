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
struct uart_port {TYPE_1__* state; } ;
struct circ_buf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* transmit_chars ) (struct uart_port*,struct circ_buf*) ;} ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,struct circ_buf*) ; 
 TYPE_2__* sunhv_ops ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void transmit_chars(struct uart_port *port)
{
	struct circ_buf *xmit;

	if (!port->state)
		return;

	xmit = &port->state->xmit;
	if (uart_circ_empty(xmit) || uart_tx_stopped(port))
		return;

	sunhv_ops->transmit_chars(port, xmit);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}