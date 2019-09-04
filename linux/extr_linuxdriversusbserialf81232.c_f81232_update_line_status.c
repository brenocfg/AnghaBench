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
struct f81232_private {int /*<<< orphan*/  interrupt_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct f81232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void f81232_update_line_status(struct usb_serial_port *port,
				      unsigned char *data,
				      size_t actual_length)
{
	struct f81232_private *priv = usb_get_serial_port_data(port);

	if (!actual_length)
		return;

	switch (data[0] & 0x07) {
	case 0x00: /* msr change */
		dev_dbg(&port->dev, "IIR: MSR Change: %02x\n", data[0]);
		schedule_work(&priv->interrupt_work);
		break;
	case 0x02: /* tx-empty */
		break;
	case 0x04: /* rx data available */
		break;
	case 0x06: /* lsr change */
		/* we can forget it. the LSR will read from bulk-in */
		dev_dbg(&port->dev, "IIR: LSR Change: %02x\n", data[0]);
		break;
	}
}