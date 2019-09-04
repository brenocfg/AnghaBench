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
struct async_icount {scalar_t__ rng; scalar_t__ dsr; scalar_t__ dcd; scalar_t__ cts; } ;
struct usb_serial_port {int /*<<< orphan*/  lock; struct async_icount icount; int /*<<< orphan*/  port; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 unsigned long TIOCM_CD ; 
 unsigned long TIOCM_CTS ; 
 unsigned long TIOCM_DSR ; 
 unsigned long TIOCM_RNG ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool usb_serial_generic_msr_changed(struct tty_struct *tty,
				unsigned long arg, struct async_icount *cprev)
{
	struct usb_serial_port *port = tty->driver_data;
	struct async_icount cnow;
	unsigned long flags;
	bool ret;

	/*
	 * Use tty-port initialised flag to detect all hangups including the
	 * one generated at USB-device disconnect.
	 */
	if (!tty_port_initialized(&port->port))
		return true;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;				/* atomic copy*/
	spin_unlock_irqrestore(&port->lock, flags);

	ret =	((arg & TIOCM_RNG) && (cnow.rng != cprev->rng)) ||
		((arg & TIOCM_DSR) && (cnow.dsr != cprev->dsr)) ||
		((arg & TIOCM_CD)  && (cnow.dcd != cprev->dcd)) ||
		((arg & TIOCM_CTS) && (cnow.cts != cprev->cts));

	*cprev = cnow;

	return ret;
}