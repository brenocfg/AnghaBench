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
struct cp210x_serial_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp210x_gpio_remove (struct usb_serial*) ; 
 int /*<<< orphan*/  kfree (struct cp210x_serial_private*) ; 
 struct cp210x_serial_private* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static void cp210x_release(struct usb_serial *serial)
{
	struct cp210x_serial_private *priv = usb_get_serial_data(serial);

	cp210x_gpio_remove(serial);

	kfree(priv);
}