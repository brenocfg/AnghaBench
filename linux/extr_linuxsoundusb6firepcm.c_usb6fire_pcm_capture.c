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
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_runtime {int frame_bits; int buffer_size; int channels; scalar_t__ format; scalar_t__ dma_area; } ;
struct pcm_urb {unsigned int buffer; TYPE_1__* packets; } ;
struct pcm_substream {int dma_off; int /*<<< orphan*/  period_off; TYPE_2__* instance; } ;
struct pcm_runtime {int in_n_analog; } ;
struct TYPE_4__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int actual_length; scalar_t__ length; } ;

/* Variables and functions */
 int PCM_N_PACKETS_PER_URB ; 
 scalar_t__ SNDRV_PCM_FORMAT_S24_LE ; 
 scalar_t__ SNDRV_PCM_FORMAT_S32_LE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct pcm_runtime* snd_pcm_substream_chip (TYPE_2__*) ; 

__attribute__((used)) static void usb6fire_pcm_capture(struct pcm_substream *sub, struct pcm_urb *urb)
{
	int i;
	int frame;
	int frame_count;
	unsigned int total_length = 0;
	struct pcm_runtime *rt = snd_pcm_substream_chip(sub->instance);
	struct snd_pcm_runtime *alsa_rt = sub->instance->runtime;
	u32 *src = NULL;
	u32 *dest = (u32 *) (alsa_rt->dma_area + sub->dma_off
			* (alsa_rt->frame_bits >> 3));
	u32 *dest_end = (u32 *) (alsa_rt->dma_area + alsa_rt->buffer_size
			* (alsa_rt->frame_bits >> 3));
	int bytes_per_frame = alsa_rt->channels << 2;

	for (i = 0; i < PCM_N_PACKETS_PER_URB; i++) {
		/* at least 4 header bytes for valid packet.
		 * after that: 32 bits per sample for analog channels */
		if (urb->packets[i].actual_length > 4)
			frame_count = (urb->packets[i].actual_length - 4)
					/ (rt->in_n_analog << 2);
		else
			frame_count = 0;

		if (alsa_rt->format == SNDRV_PCM_FORMAT_S24_LE)
			src = (u32 *) (urb->buffer + total_length);
		else if (alsa_rt->format == SNDRV_PCM_FORMAT_S32_LE)
			src = (u32 *) (urb->buffer - 1 + total_length);
		else
			return;
		src++; /* skip leading 4 bytes of every packet */
		total_length += urb->packets[i].length;
		for (frame = 0; frame < frame_count; frame++) {
			memcpy(dest, src, bytes_per_frame);
			dest += alsa_rt->channels;
			src += rt->in_n_analog;
			sub->dma_off++;
			sub->period_off++;
			if (dest == dest_end) {
				sub->dma_off = 0;
				dest = (u32 *) alsa_rt->dma_area;
			}
		}
	}
}