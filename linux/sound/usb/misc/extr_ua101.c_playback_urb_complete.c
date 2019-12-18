#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct urb {int dummy; } ;
struct TYPE_9__ {TYPE_3__* iso_frame_desc; int /*<<< orphan*/  status; struct ua101* context; } ;
struct ua101_urb {TYPE_4__ urb; int /*<<< orphan*/  ready_list; } ;
struct TYPE_10__ {int frame_bytes; TYPE_2__* substream; } ;
struct ua101 {scalar_t__ rate_feedback_count; int /*<<< orphan*/  lock; TYPE_5__ playback; int /*<<< orphan*/  playback_tasklet; int /*<<< orphan*/  ready_playback_urbs; int /*<<< orphan*/  states; } ;
struct TYPE_8__ {int length; } ;
struct TYPE_7__ {TYPE_1__* runtime; } ;
struct TYPE_6__ {int delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  USB_PLAYBACK_RUNNING ; 
 int /*<<< orphan*/  abort_alsa_playback (struct ua101*) ; 
 int /*<<< orphan*/  abort_usb_playback (struct ua101*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void playback_urb_complete(struct urb *usb_urb)
{
	struct ua101_urb *urb = (struct ua101_urb *)usb_urb;
	struct ua101 *ua = urb->urb.context;
	unsigned long flags;

	if (unlikely(urb->urb.status == -ENOENT ||	/* unlinked */
		     urb->urb.status == -ENODEV ||	/* device removed */
		     urb->urb.status == -ECONNRESET ||	/* unlinked */
		     urb->urb.status == -ESHUTDOWN)) {	/* device disabled */
		abort_usb_playback(ua);
		abort_alsa_playback(ua);
		return;
	}

	if (test_bit(USB_PLAYBACK_RUNNING, &ua->states)) {
		/* append URB to FIFO */
		spin_lock_irqsave(&ua->lock, flags);
		list_add_tail(&urb->ready_list, &ua->ready_playback_urbs);
		if (ua->rate_feedback_count > 0)
			tasklet_schedule(&ua->playback_tasklet);
		ua->playback.substream->runtime->delay -=
				urb->urb.iso_frame_desc[0].length /
						ua->playback.frame_bytes;
		spin_unlock_irqrestore(&ua->lock, flags);
	}
}