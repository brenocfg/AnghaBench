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
struct urb {TYPE_1__* iso_frame_desc; int /*<<< orphan*/  status; struct ua101* context; } ;
struct ua101_stream {unsigned int frame_bytes; int /*<<< orphan*/  substream; } ;
struct TYPE_6__ {scalar_t__ queue_length; } ;
struct ua101 {unsigned int rate_feedback_start; int rate_feedback_count; unsigned int* rate_feedback; int /*<<< orphan*/  lock; int /*<<< orphan*/  playback_tasklet; int /*<<< orphan*/  ready_playback_urbs; int /*<<< orphan*/  states; int /*<<< orphan*/  rate_feedback_wait; TYPE_3__ playback; TYPE_2__* dev; struct ua101_stream capture; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ status; unsigned int actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALSA_CAPTURE_RUNNING ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  USB_CAPTURE_RUNNING ; 
 int /*<<< orphan*/  USB_PLAYBACK_RUNNING ; 
 int /*<<< orphan*/  abort_alsa_capture (struct ua101*) ; 
 int /*<<< orphan*/  abort_alsa_playback (struct ua101*) ; 
 int /*<<< orphan*/  abort_usb_capture (struct ua101*) ; 
 int /*<<< orphan*/  abort_usb_playback (struct ua101*) ; 
 int /*<<< orphan*/  add_with_wraparound (struct ua101*,unsigned int*,int) ; 
 int copy_capture_data (struct ua101_stream*,struct urb*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_error_string (int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void capture_urb_complete(struct urb *urb)
{
	struct ua101 *ua = urb->context;
	struct ua101_stream *stream = &ua->capture;
	unsigned long flags;
	unsigned int frames, write_ptr;
	bool do_period_elapsed;
	int err;

	if (unlikely(urb->status == -ENOENT ||		/* unlinked */
		     urb->status == -ENODEV ||		/* device removed */
		     urb->status == -ECONNRESET ||	/* unlinked */
		     urb->status == -ESHUTDOWN))	/* device disabled */
		goto stream_stopped;

	if (urb->status >= 0 && urb->iso_frame_desc[0].status >= 0)
		frames = urb->iso_frame_desc[0].actual_length /
			stream->frame_bytes;
	else
		frames = 0;

	spin_lock_irqsave(&ua->lock, flags);

	if (frames > 0 && test_bit(ALSA_CAPTURE_RUNNING, &ua->states))
		do_period_elapsed = copy_capture_data(stream, urb, frames);
	else
		do_period_elapsed = false;

	if (test_bit(USB_CAPTURE_RUNNING, &ua->states)) {
		err = usb_submit_urb(urb, GFP_ATOMIC);
		if (unlikely(err < 0)) {
			spin_unlock_irqrestore(&ua->lock, flags);
			dev_err(&ua->dev->dev, "USB request error %d: %s\n",
				err, usb_error_string(err));
			goto stream_stopped;
		}

		/* append packet size to FIFO */
		write_ptr = ua->rate_feedback_start;
		add_with_wraparound(ua, &write_ptr, ua->rate_feedback_count);
		ua->rate_feedback[write_ptr] = frames;
		if (ua->rate_feedback_count < ua->playback.queue_length) {
			ua->rate_feedback_count++;
			if (ua->rate_feedback_count ==
						ua->playback.queue_length)
				wake_up(&ua->rate_feedback_wait);
		} else {
			/*
			 * Ring buffer overflow; this happens when the playback
			 * stream is not running.  Throw away the oldest entry,
			 * so that the playback stream, when it starts, sees
			 * the most recent packet sizes.
			 */
			add_with_wraparound(ua, &ua->rate_feedback_start, 1);
		}
		if (test_bit(USB_PLAYBACK_RUNNING, &ua->states) &&
		    !list_empty(&ua->ready_playback_urbs))
			tasklet_schedule(&ua->playback_tasklet);
	}

	spin_unlock_irqrestore(&ua->lock, flags);

	if (do_period_elapsed)
		snd_pcm_period_elapsed(stream->substream);

	return;

stream_stopped:
	abort_usb_playback(ua);
	abort_usb_capture(ua);
	abort_alsa_playback(ua);
	abort_alsa_capture(ua);
}