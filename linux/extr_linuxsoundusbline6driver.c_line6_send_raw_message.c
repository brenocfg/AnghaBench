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
struct usb_line6 {int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  usbdev; scalar_t__ max_packet_size; struct line6_properties* properties; } ;
struct line6_properties {int capabilities; int /*<<< orphan*/  ep_ctrl_w; } ;

/* Variables and functions */
 int HZ ; 
 int LINE6_CAP_CONTROL_MIDI ; 
 int LINE6_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int min (scalar_t__,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int line6_send_raw_message(struct usb_line6 *line6, const char *buffer,
				  int size)
{
	int i, done = 0;
	const struct line6_properties *properties = line6->properties;

	for (i = 0; i < size; i += line6->max_packet_size) {
		int partial;
		const char *frag_buf = buffer + i;
		int frag_size = min(line6->max_packet_size, size - i);
		int retval;

		if (properties->capabilities & LINE6_CAP_CONTROL_MIDI) {
			retval = usb_interrupt_msg(line6->usbdev,
						usb_sndintpipe(line6->usbdev, properties->ep_ctrl_w),
						(char *)frag_buf, frag_size,
						&partial, LINE6_TIMEOUT * HZ);
		} else {
			retval = usb_bulk_msg(line6->usbdev,
						usb_sndbulkpipe(line6->usbdev, properties->ep_ctrl_w),
						(char *)frag_buf, frag_size,
						&partial, LINE6_TIMEOUT * HZ);
		}

		if (retval) {
			dev_err(line6->ifcdev,
				"usb_bulk_msg failed (%d)\n", retval);
			break;
		}

		done += frag_size;
	}

	return done;
}