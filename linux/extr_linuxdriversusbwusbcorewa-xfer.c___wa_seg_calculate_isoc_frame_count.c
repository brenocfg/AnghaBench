#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wa_xfer {scalar_t__ seg_size; scalar_t__ is_inbound; TYPE_2__* wa; TYPE_1__* urb; } ;
struct usb_iso_packet_descriptor {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_4__ {int quirks; } ;
struct TYPE_3__ {int number_of_packets; struct usb_iso_packet_descriptor* iso_frame_desc; } ;

/* Variables and functions */
 int WUSB_QUIRK_ALEREON_HWA_CONCAT_ISOC ; 

__attribute__((used)) static int __wa_seg_calculate_isoc_frame_count(struct wa_xfer *xfer,
	int isoc_frame_offset, int *total_size)
{
	int segment_size = 0, frame_count = 0;
	int index = isoc_frame_offset;
	struct usb_iso_packet_descriptor *iso_frame_desc =
		xfer->urb->iso_frame_desc;

	while ((index < xfer->urb->number_of_packets)
		&& ((segment_size + iso_frame_desc[index].length)
				<= xfer->seg_size)) {
		/*
		 * For Alereon HWA devices, only include an isoc frame in an
		 * out segment if it is physically contiguous with the previous
		 * frame.  This is required because those devices expect
		 * the isoc frames to be sent as a single USB transaction as
		 * opposed to one transaction per frame with standard HWA.
		 */
		if ((xfer->wa->quirks & WUSB_QUIRK_ALEREON_HWA_CONCAT_ISOC)
			&& (xfer->is_inbound == 0)
			&& (index > isoc_frame_offset)
			&& ((iso_frame_desc[index - 1].offset +
				iso_frame_desc[index - 1].length) !=
				iso_frame_desc[index].offset))
			break;

		/* this frame fits. count it. */
		++frame_count;
		segment_size += iso_frame_desc[index].length;

		/* move to the next isoc frame. */
		++index;
	}

	*total_size = segment_size;
	return frame_count;
}