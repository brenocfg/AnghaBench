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
struct urb {int number_of_packets; unsigned int transfer_buffer_length; scalar_t__ transfer_buffer; TYPE_2__* iso_frame_desc; } ;
struct snd_usb_endpoint {int stride; int /*<<< orphan*/  silence_value; TYPE_1__* chip; } ;
struct snd_urb_ctx {int packets; int* packet_size; struct urb* urb; } ;
typedef  int /*<<< orphan*/  packet_length ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {unsigned int offset; unsigned int length; } ;
struct TYPE_3__ {scalar_t__ tx_length_quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_usb_endpoint_next_packet_size (struct snd_usb_endpoint*) ; 

__attribute__((used)) static void prepare_silent_urb(struct snd_usb_endpoint *ep,
			       struct snd_urb_ctx *ctx)
{
	struct urb *urb = ctx->urb;
	unsigned int offs = 0;
	unsigned int extra = 0;
	__le32 packet_length;
	int i;

	/* For tx_length_quirk, put packet length at start of packet */
	if (ep->chip->tx_length_quirk)
		extra = sizeof(packet_length);

	for (i = 0; i < ctx->packets; ++i) {
		unsigned int offset;
		unsigned int length;
		int counts;

		if (ctx->packet_size[i])
			counts = ctx->packet_size[i];
		else
			counts = snd_usb_endpoint_next_packet_size(ep);

		length = counts * ep->stride; /* number of silent bytes */
		offset = offs * ep->stride + extra * i;
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = length + extra;
		if (extra) {
			packet_length = cpu_to_le32(length);
			memcpy(urb->transfer_buffer + offset,
			       &packet_length, sizeof(packet_length));
		}
		memset(urb->transfer_buffer + offset + extra,
		       ep->silence_value, length);
		offs += counts;
	}

	urb->number_of_packets = ctx->packets;
	urb->transfer_buffer_length = offs * ep->stride + ctx->packets * extra;
}