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
typedef  int u8 ;
struct urb {int* transfer_buffer; } ;
struct TYPE_5__ {int byte_idx; size_t marker; int channel; } ;
struct snd_usb_substream {unsigned int hwptr_done; TYPE_3__* cur_audiofmt; TYPE_2__ dsd_dop; TYPE_1__* pcm_substream; } ;
struct snd_pcm_runtime {int frame_bits; unsigned int buffer_size; int* dma_area; int channels; } ;
struct TYPE_6__ {scalar_t__ dsd_bitrev; } ;
struct TYPE_4__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int bitrev8 (int) ; 

__attribute__((used)) static inline void fill_playback_urb_dsd_dop(struct snd_usb_substream *subs,
					     struct urb *urb, unsigned int bytes)
{
	struct snd_pcm_runtime *runtime = subs->pcm_substream->runtime;
	unsigned int stride = runtime->frame_bits >> 3;
	unsigned int dst_idx = 0;
	unsigned int src_idx = subs->hwptr_done;
	unsigned int wrap = runtime->buffer_size * stride;
	u8 *dst = urb->transfer_buffer;
	u8 *src = runtime->dma_area;
	u8 marker[] = { 0x05, 0xfa };

	/*
	 * The DSP DOP format defines a way to transport DSD samples over
	 * normal PCM data endpoints. It requires stuffing of marker bytes
	 * (0x05 and 0xfa, alternating per sample frame), and then expects
	 * 2 additional bytes of actual payload. The whole frame is stored
	 * LSB.
	 *
	 * Hence, for a stereo transport, the buffer layout looks like this,
	 * where L refers to left channel samples and R to right.
	 *
	 *   L1 L2 0x05   R1 R2 0x05   L3 L4 0xfa  R3 R4 0xfa
	 *   L5 L6 0x05   R5 R6 0x05   L7 L8 0xfa  R7 R8 0xfa
	 *   .....
	 *
	 */

	while (bytes--) {
		if (++subs->dsd_dop.byte_idx == 3) {
			/* frame boundary? */
			dst[dst_idx++] = marker[subs->dsd_dop.marker];
			src_idx += 2;
			subs->dsd_dop.byte_idx = 0;

			if (++subs->dsd_dop.channel % runtime->channels == 0) {
				/* alternate the marker */
				subs->dsd_dop.marker++;
				subs->dsd_dop.marker %= ARRAY_SIZE(marker);
				subs->dsd_dop.channel = 0;
			}
		} else {
			/* stuff the DSD payload */
			int idx = (src_idx + subs->dsd_dop.byte_idx - 1) % wrap;

			if (subs->cur_audiofmt->dsd_bitrev)
				dst[dst_idx++] = bitrev8(src[idx]);
			else
				dst[dst_idx++] = src[idx];

			subs->hwptr_done++;
		}
	}
	if (subs->hwptr_done >= runtime->buffer_size * stride)
		subs->hwptr_done -= runtime->buffer_size * stride;
}