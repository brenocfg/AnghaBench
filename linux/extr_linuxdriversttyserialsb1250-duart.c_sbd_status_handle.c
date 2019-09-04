#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dsr; } ;
struct uart_port {int line; TYPE_3__* state; TYPE_1__ icount; } ;
struct sbd_port {struct uart_port port; } ;
struct TYPE_5__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_6__ {TYPE_2__ port; } ;

/* Variables and functions */
 unsigned int M_DUART_IN_PIN0_VAL ; 
 unsigned int M_DUART_IN_PIN2_VAL ; 
 int /*<<< orphan*/  R_DUART_INCHREG (int) ; 
 unsigned int S_DUART_IN_PIN_CHNG ; 
 unsigned int read_sbdshr (struct sbd_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sbd_status_handle(struct sbd_port *sport)
{
	struct uart_port *uport = &sport->port;
	unsigned int delta;

	delta = read_sbdshr(sport, R_DUART_INCHREG((uport->line) % 2));
	delta >>= (uport->line) % 2;

	if (delta & (M_DUART_IN_PIN0_VAL << S_DUART_IN_PIN_CHNG))
		uart_handle_cts_change(uport, !(delta & M_DUART_IN_PIN0_VAL));

	if (delta & (M_DUART_IN_PIN2_VAL << S_DUART_IN_PIN_CHNG))
		uport->icount.dsr++;

	if (delta & ((M_DUART_IN_PIN2_VAL | M_DUART_IN_PIN0_VAL) <<
		     S_DUART_IN_PIN_CHNG))
		wake_up_interruptible(&uport->state->port.delta_msr_wait);
}