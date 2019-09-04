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
struct usb_endpoint_descriptor {unsigned int bInterval; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int USB_SPEED_HIGH ; 
 int USB_SPEED_SUPER ; 
 char* format_endpt ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,char) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor const*) ; 
 unsigned int usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 
 unsigned int usb_endpoint_maxp_mult (struct usb_endpoint_descriptor const*) ; 
 int usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static char *usb_dump_endpoint_descriptor(int speed, char *start, char *end,
				const struct usb_endpoint_descriptor *desc)
{
	char dir, unit, *type;
	unsigned interval, bandwidth = 1;

	if (start > end)
		return start;

	dir = usb_endpoint_dir_in(desc) ? 'I' : 'O';

	if (speed == USB_SPEED_HIGH)
		bandwidth = usb_endpoint_maxp_mult(desc);

	/* this isn't checking for illegal values */
	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFER_CONTROL:
		type = "Ctrl";
		if (speed == USB_SPEED_HIGH)	/* uframes per NAK */
			interval = desc->bInterval;
		else
			interval = 0;
		dir = 'B';			/* ctrl is bidirectional */
		break;
	case USB_ENDPOINT_XFER_ISOC:
		type = "Isoc";
		interval = 1 << (desc->bInterval - 1);
		break;
	case USB_ENDPOINT_XFER_BULK:
		type = "Bulk";
		if (speed == USB_SPEED_HIGH && dir == 'O') /* uframes per NAK */
			interval = desc->bInterval;
		else
			interval = 0;
		break;
	case USB_ENDPOINT_XFER_INT:
		type = "Int.";
		if (speed == USB_SPEED_HIGH || speed >= USB_SPEED_SUPER)
			interval = 1 << (desc->bInterval - 1);
		else
			interval = desc->bInterval;
		break;
	default:	/* "can't happen" */
		return start;
	}
	interval *= (speed == USB_SPEED_HIGH ||
		     speed >= USB_SPEED_SUPER) ? 125 : 1000;
	if (interval % 1000)
		unit = 'u';
	else {
		unit = 'm';
		interval /= 1000;
	}

	start += sprintf(start, format_endpt, desc->bEndpointAddress, dir,
			 desc->bmAttributes, type,
			 usb_endpoint_maxp(desc) *
			 bandwidth,
			 interval, unit);
	return start;
}