#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int number_of_packets; scalar_t__ transfer_buffer; TYPE_1__* iso_frame_desc; } ;
struct snd_usb_substream {int dummy; } ;
typedef  int /*<<< orphan*/  packet_length ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {unsigned int length; unsigned int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_to_urb (struct snd_usb_substream*,struct urb*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int copy_to_urb_quirk(struct snd_usb_substream *subs,
				      struct urb *urb, int stride,
				      unsigned int bytes)
{
	__le32 packet_length;
	int i;

	/* Put __le32 length descriptor at start of each packet. */
	for (i = 0; i < urb->number_of_packets; i++) {
		unsigned int length = urb->iso_frame_desc[i].length;
		unsigned int offset = urb->iso_frame_desc[i].offset;

		packet_length = cpu_to_le32(length);
		offset += i * sizeof(packet_length);
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length += sizeof(packet_length);
		memcpy(urb->transfer_buffer + offset,
		       &packet_length, sizeof(packet_length));
		copy_to_urb(subs, urb, offset + sizeof(packet_length),
			    stride, length);
	}
	/* Adjust transfer size accordingly. */
	bytes += urb->number_of_packets * sizeof(packet_length);
	return bytes;
}