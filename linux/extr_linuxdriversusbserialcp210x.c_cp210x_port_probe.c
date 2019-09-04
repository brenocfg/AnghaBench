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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct cp210x_port_private {int /*<<< orphan*/  bInterfaceNumber; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cp210x_detect_swapped_line_ctl (struct usb_serial_port*) ; 
 int /*<<< orphan*/  cp210x_interface_num (struct usb_serial*) ; 
 int /*<<< orphan*/  kfree (struct cp210x_port_private*) ; 
 struct cp210x_port_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct cp210x_port_private*) ; 

__attribute__((used)) static int cp210x_port_probe(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct cp210x_port_private *port_priv;
	int ret;

	port_priv = kzalloc(sizeof(*port_priv), GFP_KERNEL);
	if (!port_priv)
		return -ENOMEM;

	port_priv->bInterfaceNumber = cp210x_interface_num(serial);

	usb_set_serial_port_data(port, port_priv);

	ret = cp210x_detect_swapped_line_ctl(port);
	if (ret) {
		kfree(port_priv);
		return ret;
	}

	return 0;
}