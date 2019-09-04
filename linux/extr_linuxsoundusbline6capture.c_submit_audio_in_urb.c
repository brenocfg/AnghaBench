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
struct usb_iso_packet_descriptor {int offset; int length; } ;
struct urb {int transfer_buffer_length; struct snd_line6_pcm* context; scalar_t__ transfer_buffer; struct usb_iso_packet_descriptor* iso_frame_desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_urbs; scalar_t__ buffer; struct urb** urbs; } ;
struct snd_line6_pcm {int max_packet_size_in; TYPE_2__* line6; TYPE_1__ in; } ;
struct TYPE_4__ {int iso_buffers; int /*<<< orphan*/  ifcdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LINE6_ISO_PACKETS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int find_first_zero_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_audio_in_urb(struct snd_line6_pcm *line6pcm)
{
	int index;
	int i, urb_size;
	int ret;
	struct urb *urb_in;

	index = find_first_zero_bit(&line6pcm->in.active_urbs,
				    line6pcm->line6->iso_buffers);

	if (index < 0 || index >= line6pcm->line6->iso_buffers) {
		dev_err(line6pcm->line6->ifcdev, "no free URB found\n");
		return -EINVAL;
	}

	urb_in = line6pcm->in.urbs[index];
	urb_size = 0;

	for (i = 0; i < LINE6_ISO_PACKETS; ++i) {
		struct usb_iso_packet_descriptor *fin =
		    &urb_in->iso_frame_desc[i];
		fin->offset = urb_size;
		fin->length = line6pcm->max_packet_size_in;
		urb_size += line6pcm->max_packet_size_in;
	}

	urb_in->transfer_buffer =
	    line6pcm->in.buffer +
	    index * LINE6_ISO_PACKETS * line6pcm->max_packet_size_in;
	urb_in->transfer_buffer_length = urb_size;
	urb_in->context = line6pcm;

	ret = usb_submit_urb(urb_in, GFP_ATOMIC);

	if (ret == 0)
		set_bit(index, &line6pcm->in.active_urbs);
	else
		dev_err(line6pcm->line6->ifcdev,
			"URB in #%d submission failed (%d)\n", index, ret);

	return 0;
}