#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zilog_channel {int /*<<< orphan*/  control; } ;
struct TYPE_7__ {int /*<<< orphan*/  dsr; } ;
struct TYPE_10__ {TYPE_3__* state; TYPE_1__ icount; } ;
struct uart_ip22zilog_port {int* curregs; unsigned char prev_status; TYPE_4__ port; int /*<<< orphan*/  tty_break; } ;
struct TYPE_8__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_9__ {TYPE_2__ port; } ;

/* Variables and functions */
 int BRKIE ; 
 unsigned char BRK_ABRT ; 
 unsigned char CTS ; 
 unsigned char DCD ; 
 size_t R15 ; 
 int /*<<< orphan*/  RES_EXT_INT ; 
 int /*<<< orphan*/  Rx_BRK ; 
 int /*<<< orphan*/  Rx_SYS ; 
 unsigned char SYNC ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 scalar_t__ ZS_WANTS_MODEM_STATUS (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_break (TYPE_4__*) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_4__*,unsigned char) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_4__*,unsigned char) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip22zilog_status_handle(struct uart_ip22zilog_port *up,
				   struct zilog_channel *channel)
{
	unsigned char status;

	status = readb(&channel->control);
	ZSDELAY();

	writeb(RES_EXT_INT, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);

	if (up->curregs[R15] & BRKIE) {
		if ((status & BRK_ABRT) && !(up->prev_status & BRK_ABRT)) {
			if (uart_handle_break(&up->port))
				up->tty_break = Rx_SYS;
			else
				up->tty_break = Rx_BRK;
		}
	}

	if (ZS_WANTS_MODEM_STATUS(up)) {
		if (status & SYNC)
			up->port.icount.dsr++;

		/* The Zilog just gives us an interrupt when DCD/CTS/etc. change.
		 * But it does not tell us which bit has changed, we have to keep
		 * track of this ourselves.
		 */
		if ((status ^ up->prev_status) ^ DCD)
			uart_handle_dcd_change(&up->port,
					       (status & DCD));
		if ((status ^ up->prev_status) ^ CTS)
			uart_handle_cts_change(&up->port,
					       (status & CTS));

		wake_up_interruptible(&up->port.state->port.delta_msr_wait);
	}

	up->prev_status = status;
}