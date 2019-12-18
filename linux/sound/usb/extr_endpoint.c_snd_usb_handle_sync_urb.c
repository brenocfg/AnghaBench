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
struct urb {TYPE_1__* iso_frame_desc; int /*<<< orphan*/  transfer_buffer; struct snd_urb_ctx* context; } ;
struct snd_usb_packet_info {int packets; int* packet_size; } ;
struct snd_usb_endpoint {scalar_t__ use_count; int next_packet_write_pos; int stride; int tenor_fb_quirk; int freqn; int freqshift; unsigned int freqmax; unsigned int freqm; int /*<<< orphan*/  lock; struct snd_usb_packet_info* next_packet; } ;
struct snd_urb_ctx {int packets; } ;
struct TYPE_2__ {scalar_t__ status; int actual_length; } ;

/* Variables and functions */
 int INT_MIN ; 
 int MAX_URBS ; 
 unsigned int le32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_pending_output_urbs (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 scalar_t__ snd_usb_endpoint_implicit_feedback_sink (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void snd_usb_handle_sync_urb(struct snd_usb_endpoint *ep,
			     struct snd_usb_endpoint *sender,
			     const struct urb *urb)
{
	int shift;
	unsigned int f;
	unsigned long flags;

	snd_BUG_ON(ep == sender);

	/*
	 * In case the endpoint is operating in implicit feedback mode, prepare
	 * a new outbound URB that has the same layout as the received packet
	 * and add it to the list of pending urbs. queue_pending_output_urbs()
	 * will take care of them later.
	 */
	if (snd_usb_endpoint_implicit_feedback_sink(ep) &&
	    ep->use_count != 0) {

		/* implicit feedback case */
		int i, bytes = 0;
		struct snd_urb_ctx *in_ctx;
		struct snd_usb_packet_info *out_packet;

		in_ctx = urb->context;

		/* Count overall packet size */
		for (i = 0; i < in_ctx->packets; i++)
			if (urb->iso_frame_desc[i].status == 0)
				bytes += urb->iso_frame_desc[i].actual_length;

		/*
		 * skip empty packets. At least M-Audio's Fast Track Ultra stops
		 * streaming once it received a 0-byte OUT URB
		 */
		if (bytes == 0)
			return;

		spin_lock_irqsave(&ep->lock, flags);
		out_packet = ep->next_packet + ep->next_packet_write_pos;

		/*
		 * Iterate through the inbound packet and prepare the lengths
		 * for the output packet. The OUT packet we are about to send
		 * will have the same amount of payload bytes per stride as the
		 * IN packet we just received. Since the actual size is scaled
		 * by the stride, use the sender stride to calculate the length
		 * in case the number of channels differ between the implicitly
		 * fed-back endpoint and the synchronizing endpoint.
		 */

		out_packet->packets = in_ctx->packets;
		for (i = 0; i < in_ctx->packets; i++) {
			if (urb->iso_frame_desc[i].status == 0)
				out_packet->packet_size[i] =
					urb->iso_frame_desc[i].actual_length / sender->stride;
			else
				out_packet->packet_size[i] = 0;
		}

		ep->next_packet_write_pos++;
		ep->next_packet_write_pos %= MAX_URBS;
		spin_unlock_irqrestore(&ep->lock, flags);
		queue_pending_output_urbs(ep);

		return;
	}

	/*
	 * process after playback sync complete
	 *
	 * Full speed devices report feedback values in 10.14 format as samples
	 * per frame, high speed devices in 16.16 format as samples per
	 * microframe.
	 *
	 * Because the Audio Class 1 spec was written before USB 2.0, many high
	 * speed devices use a wrong interpretation, some others use an
	 * entirely different format.
	 *
	 * Therefore, we cannot predict what format any particular device uses
	 * and must detect it automatically.
	 */

	if (urb->iso_frame_desc[0].status != 0 ||
	    urb->iso_frame_desc[0].actual_length < 3)
		return;

	f = le32_to_cpup(urb->transfer_buffer);
	if (urb->iso_frame_desc[0].actual_length == 3)
		f &= 0x00ffffff;
	else
		f &= 0x0fffffff;

	if (f == 0)
		return;

	if (unlikely(sender->tenor_fb_quirk)) {
		/*
		 * Devices based on Tenor 8802 chipsets (TEAC UD-H01
		 * and others) sometimes change the feedback value
		 * by +/- 0x1.0000.
		 */
		if (f < ep->freqn - 0x8000)
			f += 0xf000;
		else if (f > ep->freqn + 0x8000)
			f -= 0xf000;
	} else if (unlikely(ep->freqshift == INT_MIN)) {
		/*
		 * The first time we see a feedback value, determine its format
		 * by shifting it left or right until it matches the nominal
		 * frequency value.  This assumes that the feedback does not
		 * differ from the nominal value more than +50% or -25%.
		 */
		shift = 0;
		while (f < ep->freqn - ep->freqn / 4) {
			f <<= 1;
			shift++;
		}
		while (f > ep->freqn + ep->freqn / 2) {
			f >>= 1;
			shift--;
		}
		ep->freqshift = shift;
	} else if (ep->freqshift >= 0)
		f <<= ep->freqshift;
	else
		f >>= -ep->freqshift;

	if (likely(f >= ep->freqn - ep->freqn / 8 && f <= ep->freqmax)) {
		/*
		 * If the frequency looks valid, set it.
		 * This value is referred to in prepare_playback_urb().
		 */
		spin_lock_irqsave(&ep->lock, flags);
		ep->freqm = f;
		spin_unlock_irqrestore(&ep->lock, flags);
	} else {
		/*
		 * Out of range; maybe the shift value is wrong.
		 * Reset it so that we autodetect again the next time.
		 */
		ep->freqshift = INT_MIN;
	}
}