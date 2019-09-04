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
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct edgeport_port {unsigned int shadow_mcr; int /*<<< orphan*/  ep_lock; } ;

/* Variables and functions */
 unsigned int MCR_DTR ; 
 unsigned int MCR_LOOPBACK ; 
 unsigned int MCR_RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  restore_mcr (struct edgeport_port*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct edgeport_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int edge_tiocmset(struct tty_struct *tty,
					unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct edgeport_port *edge_port = usb_get_serial_port_data(port);
	unsigned int mcr;
	unsigned long flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	mcr = edge_port->shadow_mcr;
	if (set & TIOCM_RTS)
		mcr |= MCR_RTS;
	if (set & TIOCM_DTR)
		mcr |= MCR_DTR;
	if (set & TIOCM_LOOP)
		mcr |= MCR_LOOPBACK;

	if (clear & TIOCM_RTS)
		mcr &= ~MCR_RTS;
	if (clear & TIOCM_DTR)
		mcr &= ~MCR_DTR;
	if (clear & TIOCM_LOOP)
		mcr &= ~MCR_LOOPBACK;

	edge_port->shadow_mcr = mcr;
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	restore_mcr(edge_port, mcr);
	return 0;
}