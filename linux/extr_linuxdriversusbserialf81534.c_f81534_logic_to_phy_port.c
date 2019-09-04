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
struct usb_serial_port {int port_number; int /*<<< orphan*/  serial; } ;
struct usb_serial {int dummy; } ;
struct f81534_serial_private {int* conf_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int F81534_NUM_PORT ; 
 int F81534_PORT_UNAVAILABLE ; 
 struct f81534_serial_private* usb_get_serial_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f81534_logic_to_phy_port(struct usb_serial *serial,
					struct usb_serial_port *port)
{
	struct f81534_serial_private *serial_priv =
			usb_get_serial_data(port->serial);
	int count = 0;
	int i;

	for (i = 0; i < F81534_NUM_PORT; ++i) {
		if (serial_priv->conf_data[i] & F81534_PORT_UNAVAILABLE)
			continue;

		if (port->port_number == count)
			return i;

		++count;
	}

	return -ENODEV;
}