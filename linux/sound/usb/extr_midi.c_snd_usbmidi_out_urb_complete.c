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
struct urb {scalar_t__ status; struct out_urb_context* context; } ;
struct snd_usb_midi_out_endpoint {int active_urbs; int drain_urbs; TYPE_1__* umidi; int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  drain_wait; struct out_urb_context* urbs; } ;
struct out_urb_context {struct snd_usb_midi_out_endpoint* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_timer; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ERROR_DELAY_JIFFIES ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_usbmidi_do_output (struct snd_usb_midi_out_endpoint*) ; 
 int snd_usbmidi_urb_error (struct urb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_usbmidi_out_urb_complete(struct urb *urb)
{
	struct out_urb_context *context = urb->context;
	struct snd_usb_midi_out_endpoint *ep = context->ep;
	unsigned int urb_index;
	unsigned long flags;

	spin_lock_irqsave(&ep->buffer_lock, flags);
	urb_index = context - ep->urbs;
	ep->active_urbs &= ~(1 << urb_index);
	if (unlikely(ep->drain_urbs)) {
		ep->drain_urbs &= ~(1 << urb_index);
		wake_up(&ep->drain_wait);
	}
	spin_unlock_irqrestore(&ep->buffer_lock, flags);
	if (urb->status < 0) {
		int err = snd_usbmidi_urb_error(urb);
		if (err < 0) {
			if (err != -ENODEV)
				mod_timer(&ep->umidi->error_timer,
					  jiffies + ERROR_DELAY_JIFFIES);
			return;
		}
	}
	snd_usbmidi_do_output(ep);
}