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
struct urb {scalar_t__ status; int /*<<< orphan*/  dev; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; struct snd_usb_midi_in_endpoint* context; } ;
struct snd_usb_midi_in_endpoint {int error_resubmit; TYPE_2__* umidi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  error_timer; TYPE_1__* usb_protocol_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* input ) (struct snd_usb_midi_in_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ERROR_DELAY_JIFFIES ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dump_urb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_usbmidi_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int snd_usbmidi_urb_error (struct urb*) ; 
 int /*<<< orphan*/  stub1 (struct snd_usb_midi_in_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_usbmidi_in_urb_complete(struct urb *urb)
{
	struct snd_usb_midi_in_endpoint *ep = urb->context;

	if (urb->status == 0) {
		dump_urb("received", urb->transfer_buffer, urb->actual_length);
		ep->umidi->usb_protocol_ops->input(ep, urb->transfer_buffer,
						   urb->actual_length);
	} else {
		int err = snd_usbmidi_urb_error(urb);
		if (err < 0) {
			if (err != -ENODEV) {
				ep->error_resubmit = 1;
				mod_timer(&ep->umidi->error_timer,
					  jiffies + ERROR_DELAY_JIFFIES);
			}
			return;
		}
	}

	urb->dev = ep->umidi->dev;
	snd_usbmidi_submit_urb(urb, GFP_ATOMIC);
}