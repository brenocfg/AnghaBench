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
struct snd_usb_endpoint {int datainterval; int stride; int silence_value; int freqmax; int freqn; unsigned int maxpacksize; unsigned int curpacksize; unsigned int syncinterval; unsigned int nurbs; int /*<<< orphan*/  pipe; TYPE_1__* chip; struct snd_urb_ctx* urb; void* max_urb_frames; scalar_t__ fill_max; } ;
struct snd_urb_ctx {unsigned int index; unsigned int packets; unsigned int buffer_size; int /*<<< orphan*/  ready_list; TYPE_2__* urb; struct snd_usb_endpoint* ep; } ;
struct audioformat {int datainterval; scalar_t__ fmt_type; scalar_t__ dsd_dop; } ;
typedef  int snd_pcm_format_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int interval; int /*<<< orphan*/  complete; struct snd_urb_ctx* context; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_length_quirk; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int MAX_PACKS ; 
 unsigned int MAX_PACKS_HS ; 
 unsigned int MAX_QUEUE ; 
 unsigned int MAX_URBS ; 
#define  SNDRV_PCM_FORMAT_DSD_U16_BE 133 
#define  SNDRV_PCM_FORMAT_DSD_U16_LE 132 
#define  SNDRV_PCM_FORMAT_DSD_U32_BE 131 
#define  SNDRV_PCM_FORMAT_DSD_U32_LE 130 
#define  SNDRV_PCM_FORMAT_DSD_U8 129 
#define  SNDRV_PCM_FORMAT_U8 128 
 scalar_t__ UAC_FORMAT_TYPE_II ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_WIRELESS ; 
 unsigned int max (unsigned int,unsigned int) ; 
 void* min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  release_urbs (struct snd_usb_endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_complete_urb ; 
 unsigned int snd_pcm_format_physical_width (int) ; 
 scalar_t__ snd_usb_endpoint_implicit_feedback_sink (struct snd_usb_endpoint*) ; 
 scalar_t__ snd_usb_get_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* usb_alloc_urb (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int data_ep_set_params(struct snd_usb_endpoint *ep,
			      snd_pcm_format_t pcm_format,
			      unsigned int channels,
			      unsigned int period_bytes,
			      unsigned int frames_per_period,
			      unsigned int periods_per_buffer,
			      struct audioformat *fmt,
			      struct snd_usb_endpoint *sync_ep)
{
	unsigned int maxsize, minsize, packs_per_ms, max_packs_per_urb;
	unsigned int max_packs_per_period, urbs_per_period, urb_packs;
	unsigned int max_urbs, i;
	int frame_bits = snd_pcm_format_physical_width(pcm_format) * channels;
	int tx_length_quirk = (ep->chip->tx_length_quirk &&
			       usb_pipeout(ep->pipe));

	if (pcm_format == SNDRV_PCM_FORMAT_DSD_U16_LE && fmt->dsd_dop) {
		/*
		 * When operating in DSD DOP mode, the size of a sample frame
		 * in hardware differs from the actual physical format width
		 * because we need to make room for the DOP markers.
		 */
		frame_bits += channels << 3;
	}

	ep->datainterval = fmt->datainterval;
	ep->stride = frame_bits >> 3;

	switch (pcm_format) {
	case SNDRV_PCM_FORMAT_U8:
		ep->silence_value = 0x80;
		break;
	case SNDRV_PCM_FORMAT_DSD_U8:
	case SNDRV_PCM_FORMAT_DSD_U16_LE:
	case SNDRV_PCM_FORMAT_DSD_U32_LE:
	case SNDRV_PCM_FORMAT_DSD_U16_BE:
	case SNDRV_PCM_FORMAT_DSD_U32_BE:
		ep->silence_value = 0x69;
		break;
	default:
		ep->silence_value = 0;
	}

	/* assume max. frequency is 50% higher than nominal */
	ep->freqmax = ep->freqn + (ep->freqn >> 1);
	/* Round up freqmax to nearest integer in order to calculate maximum
	 * packet size, which must represent a whole number of frames.
	 * This is accomplished by adding 0x0.ffff before converting the
	 * Q16.16 format into integer.
	 * In order to accurately calculate the maximum packet size when
	 * the data interval is more than 1 (i.e. ep->datainterval > 0),
	 * multiply by the data interval prior to rounding. For instance,
	 * a freqmax of 41 kHz will result in a max packet size of 6 (5.125)
	 * frames with a data interval of 1, but 11 (10.25) frames with a
	 * data interval of 2.
	 * (ep->freqmax << ep->datainterval overflows at 8.192 MHz for the
	 * maximum datainterval value of 3, at USB full speed, higher for
	 * USB high speed, noting that ep->freqmax is in units of
	 * frames per packet in Q16.16 format.)
	 */
	maxsize = (((ep->freqmax << ep->datainterval) + 0xffff) >> 16) *
			 (frame_bits >> 3);
	if (tx_length_quirk)
		maxsize += sizeof(__le32); /* Space for length descriptor */
	/* but wMaxPacketSize might reduce this */
	if (ep->maxpacksize && ep->maxpacksize < maxsize) {
		/* whatever fits into a max. size packet */
		unsigned int data_maxsize = maxsize = ep->maxpacksize;

		if (tx_length_quirk)
			/* Need to remove the length descriptor to calc freq */
			data_maxsize -= sizeof(__le32);
		ep->freqmax = (data_maxsize / (frame_bits >> 3))
				<< (16 - ep->datainterval);
	}

	if (ep->fill_max)
		ep->curpacksize = ep->maxpacksize;
	else
		ep->curpacksize = maxsize;

	if (snd_usb_get_speed(ep->chip->dev) != USB_SPEED_FULL) {
		packs_per_ms = 8 >> ep->datainterval;
		max_packs_per_urb = MAX_PACKS_HS;
	} else {
		packs_per_ms = 1;
		max_packs_per_urb = MAX_PACKS;
	}
	if (sync_ep && !snd_usb_endpoint_implicit_feedback_sink(ep))
		max_packs_per_urb = min(max_packs_per_urb,
					1U << sync_ep->syncinterval);
	max_packs_per_urb = max(1u, max_packs_per_urb >> ep->datainterval);

	/*
	 * Capture endpoints need to use small URBs because there's no way
	 * to tell in advance where the next period will end, and we don't
	 * want the next URB to complete much after the period ends.
	 *
	 * Playback endpoints with implicit sync much use the same parameters
	 * as their corresponding capture endpoint.
	 */
	if (usb_pipein(ep->pipe) ||
			snd_usb_endpoint_implicit_feedback_sink(ep)) {

		urb_packs = packs_per_ms;
		/*
		 * Wireless devices can poll at a max rate of once per 4ms.
		 * For dataintervals less than 5, increase the packet count to
		 * allow the host controller to use bursting to fill in the
		 * gaps.
		 */
		if (snd_usb_get_speed(ep->chip->dev) == USB_SPEED_WIRELESS) {
			int interval = ep->datainterval;
			while (interval < 5) {
				urb_packs <<= 1;
				++interval;
			}
		}
		/* make capture URBs <= 1 ms and smaller than a period */
		urb_packs = min(max_packs_per_urb, urb_packs);
		while (urb_packs > 1 && urb_packs * maxsize >= period_bytes)
			urb_packs >>= 1;
		ep->nurbs = MAX_URBS;

	/*
	 * Playback endpoints without implicit sync are adjusted so that
	 * a period fits as evenly as possible in the smallest number of
	 * URBs.  The total number of URBs is adjusted to the size of the
	 * ALSA buffer, subject to the MAX_URBS and MAX_QUEUE limits.
	 */
	} else {
		/* determine how small a packet can be */
		minsize = (ep->freqn >> (16 - ep->datainterval)) *
				(frame_bits >> 3);
		/* with sync from device, assume it can be 12% lower */
		if (sync_ep)
			minsize -= minsize >> 3;
		minsize = max(minsize, 1u);

		/* how many packets will contain an entire ALSA period? */
		max_packs_per_period = DIV_ROUND_UP(period_bytes, minsize);

		/* how many URBs will contain a period? */
		urbs_per_period = DIV_ROUND_UP(max_packs_per_period,
				max_packs_per_urb);
		/* how many packets are needed in each URB? */
		urb_packs = DIV_ROUND_UP(max_packs_per_period, urbs_per_period);

		/* limit the number of frames in a single URB */
		ep->max_urb_frames = DIV_ROUND_UP(frames_per_period,
					urbs_per_period);

		/* try to use enough URBs to contain an entire ALSA buffer */
		max_urbs = min((unsigned) MAX_URBS,
				MAX_QUEUE * packs_per_ms / urb_packs);
		ep->nurbs = min(max_urbs, urbs_per_period * periods_per_buffer);
	}

	/* allocate and initialize data urbs */
	for (i = 0; i < ep->nurbs; i++) {
		struct snd_urb_ctx *u = &ep->urb[i];
		u->index = i;
		u->ep = ep;
		u->packets = urb_packs;
		u->buffer_size = maxsize * u->packets;

		if (fmt->fmt_type == UAC_FORMAT_TYPE_II)
			u->packets++; /* for transfer delimiter */
		u->urb = usb_alloc_urb(u->packets, GFP_KERNEL);
		if (!u->urb)
			goto out_of_memory;

		u->urb->transfer_buffer =
			usb_alloc_coherent(ep->chip->dev, u->buffer_size,
					   GFP_KERNEL, &u->urb->transfer_dma);
		if (!u->urb->transfer_buffer)
			goto out_of_memory;
		u->urb->pipe = ep->pipe;
		u->urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		u->urb->interval = 1 << ep->datainterval;
		u->urb->context = u;
		u->urb->complete = snd_complete_urb;
		INIT_LIST_HEAD(&u->ready_list);
	}

	return 0;

out_of_memory:
	release_urbs(ep, 0);
	return -ENOMEM;
}