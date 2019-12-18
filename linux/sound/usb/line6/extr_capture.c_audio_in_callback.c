#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_iso_packet_descriptor {int offset; int actual_length; int /*<<< orphan*/  status; } ;
struct urb {char* transfer_buffer; struct usb_iso_packet_descriptor* iso_frame_desc; int /*<<< orphan*/  start_frame; scalar_t__ context; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  running; int /*<<< orphan*/  unlink_urbs; int /*<<< orphan*/  active_urbs; struct urb** urbs; int /*<<< orphan*/  last_frame; } ;
struct snd_line6_pcm {int max_packet_size_in; char* prev_fbuf; int prev_fsize; TYPE_4__ in; TYPE_3__* properties; TYPE_1__* line6; } ;
struct TYPE_6__ {int channels_max; } ;
struct TYPE_7__ {int bytes_per_channel; TYPE_2__ capture_hw; } ;
struct TYPE_5__ {int iso_buffers; int /*<<< orphan*/  ifcdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_MSG (int,char*) ; 
 int /*<<< orphan*/  EXDEV ; 
 int LINE6_ISO_PACKETS ; 
 int /*<<< orphan*/  LINE6_STREAM_IMPULSE ; 
 int /*<<< orphan*/  LINE6_STREAM_PCM ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  line6_capture_check_period (struct snd_line6_pcm*,int) ; 
 int /*<<< orphan*/  line6_capture_copy (struct snd_line6_pcm*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_audio_in_urb (struct snd_line6_pcm*) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audio_in_callback(struct urb *urb)
{
	int i, index, length = 0, shutdown = 0;
	unsigned long flags;

	struct snd_line6_pcm *line6pcm = (struct snd_line6_pcm *)urb->context;

	line6pcm->in.last_frame = urb->start_frame;

	/* find index of URB */
	for (index = 0; index < line6pcm->line6->iso_buffers; ++index)
		if (urb == line6pcm->in.urbs[index])
			break;

	spin_lock_irqsave(&line6pcm->in.lock, flags);

	for (i = 0; i < LINE6_ISO_PACKETS; ++i) {
		char *fbuf;
		int fsize;
		struct usb_iso_packet_descriptor *fin = &urb->iso_frame_desc[i];

		if (fin->status == -EXDEV) {
			shutdown = 1;
			break;
		}

		fbuf = urb->transfer_buffer + fin->offset;
		fsize = fin->actual_length;

		if (fsize > line6pcm->max_packet_size_in) {
			dev_err(line6pcm->line6->ifcdev,
				"driver and/or device bug: packet too large (%d > %d)\n",
				fsize, line6pcm->max_packet_size_in);
		}

		length += fsize;

		BUILD_BUG_ON_MSG(LINE6_ISO_PACKETS != 1,
			"The following code assumes LINE6_ISO_PACKETS == 1");
		/* TODO:
		 * Also, if iso_buffers != 2, the prev frame is almost random at
		 * playback side.
		 * This needs to be redesigned. It should be "stable", but we may
		 * experience sync problems on such high-speed configs.
		 */

		line6pcm->prev_fbuf = fbuf;
		line6pcm->prev_fsize = fsize /
			(line6pcm->properties->bytes_per_channel *
			line6pcm->properties->capture_hw.channels_max);

		if (!test_bit(LINE6_STREAM_IMPULSE, &line6pcm->in.running) &&
		    test_bit(LINE6_STREAM_PCM, &line6pcm->in.running) &&
		    fsize > 0)
			line6_capture_copy(line6pcm, fbuf, fsize);
	}

	clear_bit(index, &line6pcm->in.active_urbs);

	if (test_and_clear_bit(index, &line6pcm->in.unlink_urbs))
		shutdown = 1;

	if (!shutdown) {
		submit_audio_in_urb(line6pcm);

		if (!test_bit(LINE6_STREAM_IMPULSE, &line6pcm->in.running) &&
		    test_bit(LINE6_STREAM_PCM, &line6pcm->in.running))
			line6_capture_check_period(line6pcm, length);
	}

	spin_unlock_irqrestore(&line6pcm->in.lock, flags);
}