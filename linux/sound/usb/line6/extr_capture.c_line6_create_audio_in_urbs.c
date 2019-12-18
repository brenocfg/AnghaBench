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
struct usb_line6 {int iso_buffers; TYPE_2__* properties; int /*<<< orphan*/  usbdev; } ;
struct urb {int start_frame; int /*<<< orphan*/  complete; scalar_t__ error_count; int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct urb** urbs; } ;
struct snd_line6_pcm {TYPE_1__ in; struct usb_line6* line6; } ;
struct TYPE_4__ {int ep_audio_r; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LINE6_ISO_INTERVAL ; 
 int /*<<< orphan*/  LINE6_ISO_PACKETS ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int /*<<< orphan*/  audio_in_callback ; 
 struct urb** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int) ; 

int line6_create_audio_in_urbs(struct snd_line6_pcm *line6pcm)
{
	struct usb_line6 *line6 = line6pcm->line6;
	int i;

	line6pcm->in.urbs = kcalloc(line6->iso_buffers, sizeof(struct urb *),
				    GFP_KERNEL);
	if (line6pcm->in.urbs == NULL)
		return -ENOMEM;

	/* create audio URBs and fill in constant values: */
	for (i = 0; i < line6->iso_buffers; ++i) {
		struct urb *urb;

		/* URB for audio in: */
		urb = line6pcm->in.urbs[i] =
		    usb_alloc_urb(LINE6_ISO_PACKETS, GFP_KERNEL);

		if (urb == NULL)
			return -ENOMEM;

		urb->dev = line6->usbdev;
		urb->pipe =
		    usb_rcvisocpipe(line6->usbdev,
				    line6->properties->ep_audio_r &
				    USB_ENDPOINT_NUMBER_MASK);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->start_frame = -1;
		urb->number_of_packets = LINE6_ISO_PACKETS;
		urb->interval = LINE6_ISO_INTERVAL;
		urb->error_count = 0;
		urb->complete = audio_in_callback;
	}

	return 0;
}