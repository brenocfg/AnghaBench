#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {scalar_t__ transfer_buffer_length; int /*<<< orphan*/  dev; int /*<<< orphan*/  transfer_buffer; } ;
struct snd_usb_midi_out_endpoint {unsigned int next_urb; int active_urbs; int /*<<< orphan*/  buffer_lock; TYPE_3__* umidi; TYPE_1__* urbs; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_2__* usb_protocol_ops; scalar_t__ disconnected; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* output ) (struct snd_usb_midi_out_endpoint*,struct urb*) ;} ;
struct TYPE_4__ {struct urb* urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int OUTPUT_URBS ; 
 int /*<<< orphan*/  dump_urb (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ snd_usbmidi_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_usb_midi_out_endpoint*,struct urb*) ; 

__attribute__((used)) static void snd_usbmidi_do_output(struct snd_usb_midi_out_endpoint *ep)
{
	unsigned int urb_index;
	struct urb *urb;
	unsigned long flags;

	spin_lock_irqsave(&ep->buffer_lock, flags);
	if (ep->umidi->disconnected) {
		spin_unlock_irqrestore(&ep->buffer_lock, flags);
		return;
	}

	urb_index = ep->next_urb;
	for (;;) {
		if (!(ep->active_urbs & (1 << urb_index))) {
			urb = ep->urbs[urb_index].urb;
			urb->transfer_buffer_length = 0;
			ep->umidi->usb_protocol_ops->output(ep, urb);
			if (urb->transfer_buffer_length == 0)
				break;

			dump_urb("sending", urb->transfer_buffer,
				 urb->transfer_buffer_length);
			urb->dev = ep->umidi->dev;
			if (snd_usbmidi_submit_urb(urb, GFP_ATOMIC) < 0)
				break;
			ep->active_urbs |= 1 << urb_index;
		}
		if (++urb_index >= OUTPUT_URBS)
			urb_index = 0;
		if (urb_index == ep->next_urb)
			break;
	}
	ep->next_urb = urb_index;
	spin_unlock_irqrestore(&ep->buffer_lock, flags);
}