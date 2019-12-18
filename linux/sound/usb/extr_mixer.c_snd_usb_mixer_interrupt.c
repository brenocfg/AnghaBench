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
struct usb_mixer_interface {scalar_t__ protocol; TYPE_2__* chip; } ;
struct urb {int actual_length; int status; TYPE_1__* dev; struct uac2_interrupt_data_msg* transfer_buffer; struct usb_mixer_interface* context; } ;
struct uac2_interrupt_data_msg {int bStatusType; int bInfo; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bAttribute; int /*<<< orphan*/  bOriginator; } ;
struct uac1_status_word {int bStatusType; int bInfo; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bAttribute; int /*<<< orphan*/  bOriginator; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOENT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int UAC1_STATUS_TYPE_MEM_CHANGED ; 
 int UAC1_STATUS_TYPE_ORIG_AUDIO_CONTROL_IF ; 
 int UAC1_STATUS_TYPE_ORIG_MASK ; 
 int UAC2_INTERRUPT_DATA_MSG_EP ; 
 int UAC2_INTERRUPT_DATA_MSG_VENDOR ; 
 scalar_t__ UAC_VERSION_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_mixer_interrupt_v2 (struct usb_mixer_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_mixer_notify_id (struct usb_mixer_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_mixer_rc_memory_change (struct usb_mixer_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_usb_mixer_interrupt(struct urb *urb)
{
	struct usb_mixer_interface *mixer = urb->context;
	int len = urb->actual_length;
	int ustatus = urb->status;

	if (ustatus != 0)
		goto requeue;

	if (mixer->protocol == UAC_VERSION_1) {
		struct uac1_status_word *status;

		for (status = urb->transfer_buffer;
		     len >= sizeof(*status);
		     len -= sizeof(*status), status++) {
			dev_dbg(&urb->dev->dev, "status interrupt: %02x %02x\n",
						status->bStatusType,
						status->bOriginator);

			/* ignore any notifications not from the control interface */
			if ((status->bStatusType & UAC1_STATUS_TYPE_ORIG_MASK) !=
				UAC1_STATUS_TYPE_ORIG_AUDIO_CONTROL_IF)
				continue;

			if (status->bStatusType & UAC1_STATUS_TYPE_MEM_CHANGED)
				snd_usb_mixer_rc_memory_change(mixer, status->bOriginator);
			else
				snd_usb_mixer_notify_id(mixer, status->bOriginator);
		}
	} else { /* UAC_VERSION_2 */
		struct uac2_interrupt_data_msg *msg;

		for (msg = urb->transfer_buffer;
		     len >= sizeof(*msg);
		     len -= sizeof(*msg), msg++) {
			/* drop vendor specific and endpoint requests */
			if ((msg->bInfo & UAC2_INTERRUPT_DATA_MSG_VENDOR) ||
			    (msg->bInfo & UAC2_INTERRUPT_DATA_MSG_EP))
				continue;

			snd_usb_mixer_interrupt_v2(mixer, msg->bAttribute,
						   le16_to_cpu(msg->wValue),
						   le16_to_cpu(msg->wIndex));
		}
	}

requeue:
	if (ustatus != -ENOENT &&
	    ustatus != -ECONNRESET &&
	    ustatus != -ESHUTDOWN) {
		urb->dev = mixer->chip->dev;
		usb_submit_urb(urb, GFP_ATOMIC);
	}
}