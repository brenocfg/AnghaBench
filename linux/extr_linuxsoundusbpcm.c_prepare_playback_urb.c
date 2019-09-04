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
typedef  int /*<<< orphan*/  u8 ;
struct urb {unsigned int transfer_buffer_length; int /*<<< orphan*/ * transfer_buffer; scalar_t__ number_of_packets; TYPE_1__* iso_frame_desc; struct snd_urb_ctx* context; } ;
struct snd_usb_substream {scalar_t__ frame_limit; scalar_t__ transfer_done; scalar_t__ fmt_type; scalar_t__ pcm_format; int hwptr_done; unsigned int last_delay; int last_frame_number; int trigger_tstamp_pending_update; TYPE_3__* pcm_substream; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_length_quirk; TYPE_2__* cur_audiofmt; struct snd_usb_endpoint* data_endpoint; } ;
struct snd_usb_endpoint {scalar_t__ max_urb_frames; unsigned int stride; } ;
struct snd_urb_ctx {int packets; int* packet_size; } ;
struct snd_pcm_runtime {int frame_bits; scalar_t__ period_size; int buffer_size; unsigned int delay; int /*<<< orphan*/  trigger_tstamp; int /*<<< orphan*/ * dma_area; } ;
struct TYPE_6__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_5__ {scalar_t__ dsd_bitrev; scalar_t__ dsd_dop; } ;
struct TYPE_4__ {unsigned int offset; unsigned int length; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_FORMAT_DSD_U16_LE ; 
 scalar_t__ SNDRV_PCM_FORMAT_DSD_U8 ; 
 scalar_t__ UAC_FORMAT_TYPE_II ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_to_urb (struct snd_usb_substream*,struct urb*,int /*<<< orphan*/ ,int,unsigned int) ; 
 unsigned int copy_to_urb_quirk (struct snd_usb_substream*,struct urb*,int,unsigned int) ; 
 int /*<<< orphan*/  fill_playback_urb_dsd_dop (struct snd_usb_substream*,struct urb*,unsigned int) ; 
 int /*<<< orphan*/  snd_pcm_gettime (struct snd_pcm_runtime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_usb_endpoint_implicit_feedback_sink (struct snd_usb_endpoint*) ; 
 unsigned int snd_usb_endpoint_next_packet_size (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_get_current_frame_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_playback_urb(struct snd_usb_substream *subs,
				 struct urb *urb)
{
	struct snd_pcm_runtime *runtime = subs->pcm_substream->runtime;
	struct snd_usb_endpoint *ep = subs->data_endpoint;
	struct snd_urb_ctx *ctx = urb->context;
	unsigned int counts, frames, bytes;
	int i, stride, period_elapsed = 0;
	unsigned long flags;

	stride = runtime->frame_bits >> 3;

	frames = 0;
	urb->number_of_packets = 0;
	spin_lock_irqsave(&subs->lock, flags);
	subs->frame_limit += ep->max_urb_frames;
	for (i = 0; i < ctx->packets; i++) {
		if (ctx->packet_size[i])
			counts = ctx->packet_size[i];
		else
			counts = snd_usb_endpoint_next_packet_size(ep);

		/* set up descriptor */
		urb->iso_frame_desc[i].offset = frames * ep->stride;
		urb->iso_frame_desc[i].length = counts * ep->stride;
		frames += counts;
		urb->number_of_packets++;
		subs->transfer_done += counts;
		if (subs->transfer_done >= runtime->period_size) {
			subs->transfer_done -= runtime->period_size;
			subs->frame_limit = 0;
			period_elapsed = 1;
			if (subs->fmt_type == UAC_FORMAT_TYPE_II) {
				if (subs->transfer_done > 0) {
					/* FIXME: fill-max mode is not
					 * supported yet */
					frames -= subs->transfer_done;
					counts -= subs->transfer_done;
					urb->iso_frame_desc[i].length =
						counts * ep->stride;
					subs->transfer_done = 0;
				}
				i++;
				if (i < ctx->packets) {
					/* add a transfer delimiter */
					urb->iso_frame_desc[i].offset =
						frames * ep->stride;
					urb->iso_frame_desc[i].length = 0;
					urb->number_of_packets++;
				}
				break;
			}
		}
		/* finish at the period boundary or after enough frames */
		if ((period_elapsed ||
				subs->transfer_done >= subs->frame_limit) &&
		    !snd_usb_endpoint_implicit_feedback_sink(ep))
			break;
	}
	bytes = frames * ep->stride;

	if (unlikely(subs->pcm_format == SNDRV_PCM_FORMAT_DSD_U16_LE &&
		     subs->cur_audiofmt->dsd_dop)) {
		fill_playback_urb_dsd_dop(subs, urb, bytes);
	} else if (unlikely(subs->pcm_format == SNDRV_PCM_FORMAT_DSD_U8 &&
			   subs->cur_audiofmt->dsd_bitrev)) {
		/* bit-reverse the bytes */
		u8 *buf = urb->transfer_buffer;
		for (i = 0; i < bytes; i++) {
			int idx = (subs->hwptr_done + i)
				% (runtime->buffer_size * stride);
			buf[i] = bitrev8(runtime->dma_area[idx]);
		}

		subs->hwptr_done += bytes;
		if (subs->hwptr_done >= runtime->buffer_size * stride)
			subs->hwptr_done -= runtime->buffer_size * stride;
	} else {
		/* usual PCM */
		if (!subs->tx_length_quirk)
			copy_to_urb(subs, urb, 0, stride, bytes);
		else
			bytes = copy_to_urb_quirk(subs, urb, stride, bytes);
			/* bytes is now amount of outgoing data */
	}

	/* update delay with exact number of samples queued */
	runtime->delay = subs->last_delay;
	runtime->delay += frames;
	subs->last_delay = runtime->delay;

	/* realign last_frame_number */
	subs->last_frame_number = usb_get_current_frame_number(subs->dev);
	subs->last_frame_number &= 0xFF; /* keep 8 LSBs */

	if (subs->trigger_tstamp_pending_update) {
		/* this is the first actual URB submitted,
		 * update trigger timestamp to reflect actual start time
		 */
		snd_pcm_gettime(runtime, &runtime->trigger_tstamp);
		subs->trigger_tstamp_pending_update = false;
	}

	spin_unlock_irqrestore(&subs->lock, flags);
	urb->transfer_buffer_length = bytes;
	if (period_elapsed)
		snd_pcm_period_elapsed(subs->pcm_substream);
}