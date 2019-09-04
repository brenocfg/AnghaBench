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
struct ftdi_private {size_t chip_type; } ;

/* Variables and functions */
 size_t FT2232C ; 
 size_t FT2232H ; 
 size_t FT232BM ; 
 size_t FT232H ; 
 size_t FT232RL ; 
 size_t FT4232H ; 
 size_t FTX ; 
 size_t SIO ; 
 int /*<<< orphan*/  dev_attr_event_char ; 
 int /*<<< orphan*/  dev_attr_latency_timer ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftdi_chip_name ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int create_sysfs_attrs(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	int retval = 0;

	/* XXX I've no idea if the original SIO supports the event_char
	 * sysfs parameter, so I'm playing it safe.  */
	if (priv->chip_type != SIO) {
		dev_dbg(&port->dev, "sysfs attributes for %s\n", ftdi_chip_name[priv->chip_type]);
		retval = device_create_file(&port->dev, &dev_attr_event_char);
		if ((!retval) &&
		    (priv->chip_type == FT232BM ||
		     priv->chip_type == FT2232C ||
		     priv->chip_type == FT232RL ||
		     priv->chip_type == FT2232H ||
		     priv->chip_type == FT4232H ||
		     priv->chip_type == FT232H ||
		     priv->chip_type == FTX)) {
			retval = device_create_file(&port->dev,
						    &dev_attr_latency_timer);
		}
	}
	return retval;
}