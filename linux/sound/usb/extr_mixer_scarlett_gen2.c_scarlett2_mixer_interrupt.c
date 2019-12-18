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
typedef  int u32 ;
struct usb_mixer_interface {TYPE_1__* chip; } ;
struct urb {int actual_length; int status; int /*<<< orphan*/  dev; scalar_t__ transfer_buffer; struct usb_mixer_interface* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOENT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SCARLETT2_USB_INTERRUPT_BUTTON_CHANGE ; 
 int SCARLETT2_USB_INTERRUPT_VOL_CHANGE ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  scarlett2_mixer_interrupt_button_change (struct usb_mixer_interface*) ; 
 int /*<<< orphan*/  scarlett2_mixer_interrupt_vol_change (struct usb_mixer_interface*) ; 
 int /*<<< orphan*/  usb_audio_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scarlett2_mixer_interrupt(struct urb *urb)
{
	struct usb_mixer_interface *mixer = urb->context;
	int len = urb->actual_length;
	int ustatus = urb->status;
	u32 data;

	if (ustatus != 0)
		goto requeue;

	if (len == 8) {
		data = le32_to_cpu(*(u32 *)urb->transfer_buffer);
		if (data & SCARLETT2_USB_INTERRUPT_VOL_CHANGE)
			scarlett2_mixer_interrupt_vol_change(mixer);
		if (data & SCARLETT2_USB_INTERRUPT_BUTTON_CHANGE)
			scarlett2_mixer_interrupt_button_change(mixer);
	} else {
		usb_audio_err(mixer->chip,
			      "scarlett mixer interrupt length %d\n", len);
	}

requeue:
	if (ustatus != -ENOENT &&
	    ustatus != -ECONNRESET &&
	    ustatus != -ESHUTDOWN) {
		urb->dev = mixer->chip->dev;
		usb_submit_urb(urb, GFP_ATOMIC);
	}
}