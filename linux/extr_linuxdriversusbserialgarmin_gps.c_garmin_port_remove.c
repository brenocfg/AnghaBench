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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; } ;
struct garmin_data {int /*<<< orphan*/  timer; int /*<<< orphan*/  write_urbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct garmin_data*) ; 
 struct garmin_data* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int garmin_port_remove(struct usb_serial_port *port)
{
	struct garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	usb_kill_anchored_urbs(&garmin_data_p->write_urbs);
	usb_kill_urb(port->interrupt_in_urb);
	del_timer_sync(&garmin_data_p->timer);
	kfree(garmin_data_p);
	return 0;
}