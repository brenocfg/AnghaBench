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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct ftdi_private {scalar_t__ chip_type; int latency; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FT8U232AM ; 
 scalar_t__ SIO ; 
 int _read_latency_timer (struct usb_serial_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int read_latency_timer(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	int rv;

	if (priv->chip_type == SIO || priv->chip_type == FT8U232AM)
		return -EINVAL;

	rv = _read_latency_timer(port);
	if (rv < 0) {
		dev_err(&port->dev, "Unable to read latency timer: %i\n", rv);
		return rv;
	}

	priv->latency = rv;

	return 0;
}