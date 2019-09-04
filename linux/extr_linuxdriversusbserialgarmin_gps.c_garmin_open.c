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
struct usb_serial_port {int /*<<< orphan*/  read_urb; } ;
struct tty_struct {int dummy; } ;
struct garmin_data {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; scalar_t__ count; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_SESSION_REPLY1_SEEN ; 
 scalar_t__ STATE_ACTIVE ; 
 scalar_t__ STATE_RESET ; 
 int garmin_init_session (struct usb_serial_port*) ; 
 int /*<<< orphan*/  initial_mode ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct garmin_data* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int garmin_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	unsigned long flags;
	int status = 0;
	struct garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	garmin_data_p->mode  = initial_mode;
	garmin_data_p->count = 0;
	garmin_data_p->flags &= FLAGS_SESSION_REPLY1_SEEN;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	/* shutdown any bulk reads that might be going on */
	usb_kill_urb(port->read_urb);

	if (garmin_data_p->state == STATE_RESET)
		status = garmin_init_session(port);

	garmin_data_p->state = STATE_ACTIVE;
	return status;
}