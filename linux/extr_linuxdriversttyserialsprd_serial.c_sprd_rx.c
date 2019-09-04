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
struct TYPE_3__ {int /*<<< orphan*/  rx; } ;
struct uart_port {TYPE_1__ icount; TYPE_2__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_LSR ; 
 unsigned int SPRD_LSR_BI ; 
 unsigned int SPRD_LSR_FE ; 
 unsigned int SPRD_LSR_OE ; 
 unsigned int SPRD_LSR_PE ; 
 int /*<<< orphan*/  SPRD_RXD ; 
 int /*<<< orphan*/  SPRD_STS1 ; 
 unsigned int SPRD_TIMEOUT ; 
 unsigned int TTY_NORMAL ; 
 scalar_t__ handle_lsr_errors (struct uart_port*,unsigned int*,unsigned int*) ; 
 int serial_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void sprd_rx(struct uart_port *port)
{
	struct tty_port *tty = &port->state->port;
	unsigned int ch, flag, lsr, max_count = SPRD_TIMEOUT;

	while ((serial_in(port, SPRD_STS1) & 0x00ff) && max_count--) {
		lsr = serial_in(port, SPRD_LSR);
		ch = serial_in(port, SPRD_RXD);
		flag = TTY_NORMAL;
		port->icount.rx++;

		if (lsr & (SPRD_LSR_BI | SPRD_LSR_PE |
			SPRD_LSR_FE | SPRD_LSR_OE))
			if (handle_lsr_errors(port, &lsr, &flag))
				continue;
		if (uart_handle_sysrq_char(port, ch))
			continue;

		uart_insert_char(port, lsr, SPRD_LSR_OE, ch, flag);
	}

	tty_flip_buffer_push(tty);
}