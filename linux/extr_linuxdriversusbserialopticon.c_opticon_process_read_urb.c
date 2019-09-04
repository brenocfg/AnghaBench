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
struct urb {unsigned char* transfer_buffer; int actual_length; struct usb_serial_port* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char const,...) ; 
 int /*<<< orphan*/  opticon_process_data_packet (struct usb_serial_port*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  opticon_process_status_packet (struct usb_serial_port*,unsigned char const*,size_t) ; 

__attribute__((used)) static void opticon_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	const unsigned char *hdr = urb->transfer_buffer;
	const unsigned char *data = hdr + 2;
	size_t data_len = urb->actual_length - 2;

	if (urb->actual_length <= 2) {
		dev_dbg(&port->dev, "malformed packet received: %d bytes\n",
							urb->actual_length);
		return;
	}
	/*
	 * Data from the device comes with a 2 byte header:
	 *
	 * <0x00><0x00>data...
	 *      This is real data to be sent to the tty layer
	 * <0x00><0x01>level
	 *      This is a CTS level change, the third byte is the CTS
	 *      value (0 for low, 1 for high).
	 */
	if ((hdr[0] == 0x00) && (hdr[1] == 0x00)) {
		opticon_process_data_packet(port, data, data_len);
	} else if ((hdr[0] == 0x00) && (hdr[1] == 0x01)) {
		opticon_process_status_packet(port, data, data_len);
	} else {
		dev_dbg(&port->dev, "unknown packet received: %02x %02x\n",
							hdr[0], hdr[1]);
	}
}