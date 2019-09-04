#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ console; int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_5__ {int rx; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct usb_serial_port {TYPE_2__ port; scalar_t__ sysrq; TYPE_1__ icount; int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;
struct ftdi_private {char prev_status; int transmit_empty; } ;

/* Variables and functions */
 char FTDI_RS0_CTS ; 
 char FTDI_RS0_DSR ; 
 char FTDI_RS0_RI ; 
 char FTDI_RS0_RLSD ; 
 char FTDI_RS_BI ; 
 char FTDI_RS_ERR_MASK ; 
 char FTDI_RS_FE ; 
 char FTDI_RS_OE ; 
 char FTDI_RS_PE ; 
 char FTDI_RS_TEMT ; 
 char FTDI_STATUS_B0_MASK ; 
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (TYPE_2__*,char,char) ; 
 int /*<<< orphan*/  tty_insert_flip_string_fixed_flag (TYPE_2__*,char*,char,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_serial_handle_break (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_handle_dcd_change (struct usb_serial_port*,struct tty_struct*,char) ; 
 int /*<<< orphan*/  usb_serial_handle_sysrq_char (struct usb_serial_port*,char) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftdi_process_packet(struct usb_serial_port *port,
		struct ftdi_private *priv, char *packet, int len)
{
	int i;
	char status;
	char flag;
	char *ch;

	if (len < 2) {
		dev_dbg(&port->dev, "malformed packet\n");
		return 0;
	}

	/* Compare new line status to the old one, signal if different/
	   N.B. packet may be processed more than once, but differences
	   are only processed once.  */
	status = packet[0] & FTDI_STATUS_B0_MASK;
	if (status != priv->prev_status) {
		char diff_status = status ^ priv->prev_status;

		if (diff_status & FTDI_RS0_CTS)
			port->icount.cts++;
		if (diff_status & FTDI_RS0_DSR)
			port->icount.dsr++;
		if (diff_status & FTDI_RS0_RI)
			port->icount.rng++;
		if (diff_status & FTDI_RS0_RLSD) {
			struct tty_struct *tty;

			port->icount.dcd++;
			tty = tty_port_tty_get(&port->port);
			if (tty)
				usb_serial_handle_dcd_change(port, tty,
						status & FTDI_RS0_RLSD);
			tty_kref_put(tty);
		}

		wake_up_interruptible(&port->port.delta_msr_wait);
		priv->prev_status = status;
	}

	/* save if the transmitter is empty or not */
	if (packet[1] & FTDI_RS_TEMT)
		priv->transmit_empty = 1;
	else
		priv->transmit_empty = 0;

	len -= 2;
	if (!len)
		return 0;	/* status only */

	/*
	 * Break and error status must only be processed for packets with
	 * data payload to avoid over-reporting.
	 */
	flag = TTY_NORMAL;
	if (packet[1] & FTDI_RS_ERR_MASK) {
		/* Break takes precedence over parity, which takes precedence
		 * over framing errors */
		if (packet[1] & FTDI_RS_BI) {
			flag = TTY_BREAK;
			port->icount.brk++;
			usb_serial_handle_break(port);
		} else if (packet[1] & FTDI_RS_PE) {
			flag = TTY_PARITY;
			port->icount.parity++;
		} else if (packet[1] & FTDI_RS_FE) {
			flag = TTY_FRAME;
			port->icount.frame++;
		}
		/* Overrun is special, not associated with a char */
		if (packet[1] & FTDI_RS_OE) {
			port->icount.overrun++;
			tty_insert_flip_char(&port->port, 0, TTY_OVERRUN);
		}
	}

	port->icount.rx += len;
	ch = packet + 2;

	if (port->port.console && port->sysrq) {
		for (i = 0; i < len; i++, ch++) {
			if (!usb_serial_handle_sysrq_char(port, *ch))
				tty_insert_flip_char(&port->port, *ch, flag);
		}
	} else {
		tty_insert_flip_string_fixed_flag(&port->port, ch, flag, len);
	}

	return len;
}