#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_pcm_runtime {int frame_bits; int buffer_size; int channels; scalar_t__ format; scalar_t__ dma_area; } ;
struct pcm_urb {int buffer; TYPE_3__* packets; } ;
struct pcm_substream {int dma_off; int /*<<< orphan*/  period_off; TYPE_4__* instance; } ;
struct pcm_runtime {int out_n_analog; TYPE_2__* chip; } ;
struct TYPE_8__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_7__ {int length; } ;
struct TYPE_6__ {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCM_N_PACKETS_PER_URB ; 
 scalar_t__ SNDRV_PCM_FORMAT_S24_LE ; 
 scalar_t__ SNDRV_PCM_FORMAT_S32_LE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct pcm_runtime* snd_pcm_substream_chip (TYPE_4__*) ; 

__attribute__((used)) static void usb6fire_pcm_playback(struct pcm_substream *sub,
		struct pcm_urb *urb)
{
	int i;
	int frame;
	int frame_count;
	struct pcm_runtime *rt = snd_pcm_substream_chip(sub->instance);
	struct snd_pcm_runtime *alsa_rt = sub->instance->runtime;
	u32 *src = (u32 *) (alsa_rt->dma_area + sub->dma_off
			* (alsa_rt->frame_bits >> 3));
	u32 *src_end = (u32 *) (alsa_rt->dma_area + alsa_rt->buffer_size
			* (alsa_rt->frame_bits >> 3));
	u32 *dest;
	int bytes_per_frame = alsa_rt->channels << 2;

	if (alsa_rt->format == SNDRV_PCM_FORMAT_S32_LE)
		dest = (u32 *) (urb->buffer - 1);
	else if (alsa_rt->format == SNDRV_PCM_FORMAT_S24_LE)
		dest = (u32 *) (urb->buffer);
	else {
		dev_err(&rt->chip->dev->dev, "Unknown sample format.");
		return;
	}

	for (i = 0; i < PCM_N_PACKETS_PER_URB; i++) {
		/* at least 4 header bytes for valid packet.
		 * after that: 32 bits per sample for analog channels */
		if (urb->packets[i].length > 4)
			frame_count = (urb->packets[i].length - 4)
					/ (rt->out_n_analog << 2);
		else
			frame_count = 0;
		dest++; /* skip leading 4 bytes of every frame */
		for (frame = 0; frame < frame_count; frame++) {
			memcpy(dest, src, bytes_per_frame);
			src += alsa_rt->channels;
			dest += rt->out_n_analog;
			sub->dma_off++;
			sub->period_off++;
			if (src == src_end) {
				src = (u32 *) alsa_rt->dma_area;
				sub->dma_off = 0;
			}
		}
	}
}