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
struct urb {int /*<<< orphan*/  status; struct snd_urb_ctx* context; } ;
struct snd_usb_endpoint {int /*<<< orphan*/  active_mask; TYPE_1__* data_subs; TYPE_2__* chip; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  ready_playback_urbs; int /*<<< orphan*/  pipe; } ;
struct snd_urb_ctx {int /*<<< orphan*/  index; int /*<<< orphan*/  ready_list; struct snd_usb_endpoint* ep; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  shutdown; } ;
struct TYPE_3__ {struct snd_pcm_substream* pcm_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EP_FLAG_RUNNING ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_inbound_urb (struct snd_usb_endpoint*,struct snd_urb_ctx*) ; 
 int /*<<< orphan*/  prepare_outbound_urb (struct snd_usb_endpoint*,struct snd_urb_ctx*) ; 
 int /*<<< orphan*/  queue_pending_output_urbs (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  retire_inbound_urb (struct snd_usb_endpoint*,struct snd_urb_ctx*) ; 
 int /*<<< orphan*/  retire_outbound_urb (struct snd_usb_endpoint*,struct snd_urb_ctx*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (struct snd_pcm_substream*) ; 
 scalar_t__ snd_usb_endpoint_implicit_feedback_sink (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_audio_err (TYPE_2__*,char*,int) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_complete_urb(struct urb *urb)
{
	struct snd_urb_ctx *ctx = urb->context;
	struct snd_usb_endpoint *ep = ctx->ep;
	struct snd_pcm_substream *substream;
	unsigned long flags;
	int err;

	if (unlikely(urb->status == -ENOENT ||		/* unlinked */
		     urb->status == -ENODEV ||		/* device removed */
		     urb->status == -ECONNRESET ||	/* unlinked */
		     urb->status == -ESHUTDOWN))	/* device disabled */
		goto exit_clear;
	/* device disconnected */
	if (unlikely(atomic_read(&ep->chip->shutdown)))
		goto exit_clear;

	if (unlikely(!test_bit(EP_FLAG_RUNNING, &ep->flags)))
		goto exit_clear;

	if (usb_pipeout(ep->pipe)) {
		retire_outbound_urb(ep, ctx);
		/* can be stopped during retire callback */
		if (unlikely(!test_bit(EP_FLAG_RUNNING, &ep->flags)))
			goto exit_clear;

		if (snd_usb_endpoint_implicit_feedback_sink(ep)) {
			spin_lock_irqsave(&ep->lock, flags);
			list_add_tail(&ctx->ready_list, &ep->ready_playback_urbs);
			spin_unlock_irqrestore(&ep->lock, flags);
			queue_pending_output_urbs(ep);

			goto exit_clear;
		}

		prepare_outbound_urb(ep, ctx);
	} else {
		retire_inbound_urb(ep, ctx);
		/* can be stopped during retire callback */
		if (unlikely(!test_bit(EP_FLAG_RUNNING, &ep->flags)))
			goto exit_clear;

		prepare_inbound_urb(ep, ctx);
	}

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err == 0)
		return;

	usb_audio_err(ep->chip, "cannot submit urb (err = %d)\n", err);
	if (ep->data_subs && ep->data_subs->pcm_substream) {
		substream = ep->data_subs->pcm_substream;
		snd_pcm_stop_xrun(substream);
	}

exit_clear:
	clear_bit(ctx->index, &ep->active_mask);
}