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
struct urb {int transfer_buffer_length; int number_of_packets; TYPE_2__* iso_frame_desc; int /*<<< orphan*/  dev; } ;
struct snd_usb_endpoint {int type; int curpacksize; int /*<<< orphan*/  syncmaxsize; TYPE_1__* chip; } ;
struct snd_urb_ctx {int packets; struct urb* urb; } ;
struct TYPE_4__ {int offset; int length; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SND_USB_ENDPOINT_TYPE_DATA 129 
#define  SND_USB_ENDPOINT_TYPE_SYNC 128 
 int min (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void prepare_inbound_urb(struct snd_usb_endpoint *ep,
				       struct snd_urb_ctx *urb_ctx)
{
	int i, offs;
	struct urb *urb = urb_ctx->urb;

	urb->dev = ep->chip->dev; /* we need to set this at each time */

	switch (ep->type) {
	case SND_USB_ENDPOINT_TYPE_DATA:
		offs = 0;
		for (i = 0; i < urb_ctx->packets; i++) {
			urb->iso_frame_desc[i].offset = offs;
			urb->iso_frame_desc[i].length = ep->curpacksize;
			offs += ep->curpacksize;
		}

		urb->transfer_buffer_length = offs;
		urb->number_of_packets = urb_ctx->packets;
		break;

	case SND_USB_ENDPOINT_TYPE_SYNC:
		urb->iso_frame_desc[0].length = min(4u, ep->syncmaxsize);
		urb->iso_frame_desc[0].offset = 0;
		break;
	}
}