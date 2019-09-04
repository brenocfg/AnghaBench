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
struct usb_iso_packet_descriptor {int length; scalar_t__ offset; } ;
struct urb {int number_of_packets; int transfer_buffer_length; struct usb_iso_packet_descriptor* iso_frame_desc; } ;

/* Variables and functions */

__attribute__((used)) static void prepare_inurb(int number_of_packets, struct urb *iu)
{
	struct usb_iso_packet_descriptor *id;
	int p;

	iu->number_of_packets = number_of_packets;
	id = iu->iso_frame_desc;
	id->offset = 0;
	for (p = 0; p < iu->number_of_packets - 1; ++p)
		id[p + 1].offset = id[p].offset + id[p].length;

	iu->transfer_buffer_length =
		id[0].length * iu->number_of_packets;
}