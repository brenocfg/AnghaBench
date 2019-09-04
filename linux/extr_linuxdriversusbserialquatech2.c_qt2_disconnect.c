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
struct qt2_serial_private {int /*<<< orphan*/  read_urb; } ;

/* Variables and functions */
 struct qt2_serial_private* usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qt2_disconnect(struct usb_serial *serial)
{
	struct qt2_serial_private *serial_priv = usb_get_serial_data(serial);

	usb_kill_urb(serial_priv->read_urb);
}