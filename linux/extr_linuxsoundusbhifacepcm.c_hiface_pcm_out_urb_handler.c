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
struct urb {int /*<<< orphan*/  status; struct pcm_urb* context; } ;
struct pcm_urb {int /*<<< orphan*/  instance; int /*<<< orphan*/  buffer; TYPE_1__* chip; } ;
struct pcm_substream {int /*<<< orphan*/  instance; int /*<<< orphan*/  lock; scalar_t__ active; } ;
struct pcm_runtime {int panic; scalar_t__ stream_state; int stream_wait_cond; struct pcm_substream playback; int /*<<< orphan*/  stream_wait_queue; } ;
struct TYPE_2__ {struct pcm_runtime* pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCM_PACKET_SIZE ; 
 scalar_t__ STREAM_STARTING ; 
 scalar_t__ STREAM_STOPPING ; 
 int hiface_pcm_playback (struct pcm_substream*,struct pcm_urb*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hiface_pcm_out_urb_handler(struct urb *usb_urb)
{
	struct pcm_urb *out_urb = usb_urb->context;
	struct pcm_runtime *rt = out_urb->chip->pcm;
	struct pcm_substream *sub;
	bool do_period_elapsed = false;
	unsigned long flags;
	int ret;

	if (rt->panic || rt->stream_state == STREAM_STOPPING)
		return;

	if (unlikely(usb_urb->status == -ENOENT ||	/* unlinked */
		     usb_urb->status == -ENODEV ||	/* device removed */
		     usb_urb->status == -ECONNRESET ||	/* unlinked */
		     usb_urb->status == -ESHUTDOWN)) {	/* device disabled */
		goto out_fail;
	}

	if (rt->stream_state == STREAM_STARTING) {
		rt->stream_wait_cond = true;
		wake_up(&rt->stream_wait_queue);
	}

	/* now send our playback data (if a free out urb was found) */
	sub = &rt->playback;
	spin_lock_irqsave(&sub->lock, flags);
	if (sub->active)
		do_period_elapsed = hiface_pcm_playback(sub, out_urb);
	else
		memset(out_urb->buffer, 0, PCM_PACKET_SIZE);

	spin_unlock_irqrestore(&sub->lock, flags);

	if (do_period_elapsed)
		snd_pcm_period_elapsed(sub->instance);

	ret = usb_submit_urb(&out_urb->instance, GFP_ATOMIC);
	if (ret < 0)
		goto out_fail;

	return;

out_fail:
	rt->panic = true;
}