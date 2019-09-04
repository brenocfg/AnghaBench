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
struct usb_serial {int dummy; } ;
struct edgeport_serial {int /*<<< orphan*/  heartbeat_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct edgeport_serial* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static void edge_disconnect(struct usb_serial *serial)
{
	struct edgeport_serial *edge_serial = usb_get_serial_data(serial);

	cancel_delayed_work_sync(&edge_serial->heartbeat_work);
}