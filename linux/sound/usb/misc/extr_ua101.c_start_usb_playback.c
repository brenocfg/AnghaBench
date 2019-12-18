#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct urb {TYPE_2__* iso_frame_desc; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  complete; } ;
struct TYPE_7__ {unsigned int queue_length; unsigned int frame_bytes; TYPE_1__** urbs; } ;
struct ua101 {unsigned int rate_feedback_count; unsigned int* rate_feedback; size_t rate_feedback_start; TYPE_3__ playback; int /*<<< orphan*/  states; int /*<<< orphan*/  lock; int /*<<< orphan*/  rate_feedback_wait; int /*<<< orphan*/  ready_playback_urbs; int /*<<< orphan*/  playback_tasklet; } ;
struct TYPE_6__ {unsigned int length; } ;
struct TYPE_5__ {struct urb urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTF_PLAYBACK ; 
 int /*<<< orphan*/  PLAYBACK_URB_COMPLETED ; 
 int /*<<< orphan*/  USB_CAPTURE_RUNNING ; 
 int /*<<< orphan*/  USB_PLAYBACK_RUNNING ; 
 int /*<<< orphan*/  add_with_wraparound (struct ua101*,size_t*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int enable_iso_interface (struct ua101*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_playback_urb_complete ; 
 int /*<<< orphan*/  kill_stream_urbs (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_usb_playback (struct ua101*) ; 
 int submit_stream_urbs (struct ua101*,TYPE_3__*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int start_usb_playback(struct ua101 *ua)
{
	unsigned int i, frames;
	struct urb *urb;
	int err = 0;

	if (test_bit(DISCONNECTED, &ua->states))
		return -ENODEV;

	if (test_bit(USB_PLAYBACK_RUNNING, &ua->states))
		return 0;

	kill_stream_urbs(&ua->playback);
	tasklet_kill(&ua->playback_tasklet);

	err = enable_iso_interface(ua, INTF_PLAYBACK);
	if (err < 0)
		return err;

	clear_bit(PLAYBACK_URB_COMPLETED, &ua->states);
	ua->playback.urbs[0]->urb.complete =
		first_playback_urb_complete;
	spin_lock_irq(&ua->lock);
	INIT_LIST_HEAD(&ua->ready_playback_urbs);
	spin_unlock_irq(&ua->lock);

	/*
	 * We submit the initial URBs all at once, so we have to wait for the
	 * packet size FIFO to be full.
	 */
	wait_event(ua->rate_feedback_wait,
		   ua->rate_feedback_count >= ua->playback.queue_length ||
		   !test_bit(USB_CAPTURE_RUNNING, &ua->states) ||
		   test_bit(DISCONNECTED, &ua->states));
	if (test_bit(DISCONNECTED, &ua->states)) {
		stop_usb_playback(ua);
		return -ENODEV;
	}
	if (!test_bit(USB_CAPTURE_RUNNING, &ua->states)) {
		stop_usb_playback(ua);
		return -EIO;
	}

	for (i = 0; i < ua->playback.queue_length; ++i) {
		/* all initial URBs contain silence */
		spin_lock_irq(&ua->lock);
		frames = ua->rate_feedback[ua->rate_feedback_start];
		add_with_wraparound(ua, &ua->rate_feedback_start, 1);
		ua->rate_feedback_count--;
		spin_unlock_irq(&ua->lock);
		urb = &ua->playback.urbs[i]->urb;
		urb->iso_frame_desc[0].length =
			frames * ua->playback.frame_bytes;
		memset(urb->transfer_buffer, 0,
		       urb->iso_frame_desc[0].length);
	}

	set_bit(USB_PLAYBACK_RUNNING, &ua->states);
	err = submit_stream_urbs(ua, &ua->playback);
	if (err < 0)
		stop_usb_playback(ua);
	return err;
}