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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; } ;
struct usb_serial_port {int /*<<< orphan*/  port; TYPE_1__ icount; } ;
struct ssu100_port_private {int shadowLSR; int /*<<< orphan*/  status_lock; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int UART_LSR_BI ; 
 int UART_LSR_BRK_ERROR_BITS ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ssu100_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_handle_break (struct usb_serial_port*) ; 

__attribute__((used)) static void ssu100_update_lsr(struct usb_serial_port *port, u8 lsr,
			      char *tty_flag)
{
	struct ssu100_port_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->shadowLSR = lsr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	*tty_flag = TTY_NORMAL;
	if (lsr & UART_LSR_BRK_ERROR_BITS) {
		/* we always want to update icount, but we only want to
		 * update tty_flag for one case */
		if (lsr & UART_LSR_BI) {
			port->icount.brk++;
			*tty_flag = TTY_BREAK;
			usb_serial_handle_break(port);
		}
		if (lsr & UART_LSR_PE) {
			port->icount.parity++;
			if (*tty_flag == TTY_NORMAL)
				*tty_flag = TTY_PARITY;
		}
		if (lsr & UART_LSR_FE) {
			port->icount.frame++;
			if (*tty_flag == TTY_NORMAL)
				*tty_flag = TTY_FRAME;
		}
		if (lsr & UART_LSR_OE) {
			port->icount.overrun++;
			tty_insert_flip_char(&port->port, 0, TTY_OVERRUN);
		}
	}

}