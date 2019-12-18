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
struct snd_pcm_runtime {char* dma_area; scalar_t__ buffer_size; TYPE_3__* control; TYPE_2__* status; } ;
struct loopback_pcm {unsigned int buf_pos; unsigned int pcm_salign; unsigned int pcm_buffer_size; scalar_t__ silent_size; TYPE_1__* substream; } ;
typedef  unsigned int snd_pcm_uframes_t ;
struct TYPE_6__ {unsigned int appl_ptr; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct TYPE_4__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STATE_DRAINING ; 
 int /*<<< orphan*/  clear_capture_buf (struct loopback_pcm*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 scalar_t__ snd_pcm_playback_hw_avail (struct snd_pcm_runtime*) ; 

__attribute__((used)) static void copy_play_buf(struct loopback_pcm *play,
			  struct loopback_pcm *capt,
			  unsigned int bytes)
{
	struct snd_pcm_runtime *runtime = play->substream->runtime;
	char *src = runtime->dma_area;
	char *dst = capt->substream->runtime->dma_area;
	unsigned int src_off = play->buf_pos;
	unsigned int dst_off = capt->buf_pos;
	unsigned int clear_bytes = 0;

	/* check if playback is draining, trim the capture copy size
	 * when our pointer is at the end of playback ring buffer */
	if (runtime->status->state == SNDRV_PCM_STATE_DRAINING &&
	    snd_pcm_playback_hw_avail(runtime) < runtime->buffer_size) { 
	    	snd_pcm_uframes_t appl_ptr, appl_ptr1, diff;
		appl_ptr = appl_ptr1 = runtime->control->appl_ptr;
		appl_ptr1 -= appl_ptr1 % runtime->buffer_size;
		appl_ptr1 += play->buf_pos / play->pcm_salign;
		if (appl_ptr < appl_ptr1)
			appl_ptr1 -= runtime->buffer_size;
		diff = (appl_ptr - appl_ptr1) * play->pcm_salign;
		if (diff < bytes) {
			clear_bytes = bytes - diff;
			bytes = diff;
		}
	}

	for (;;) {
		unsigned int size = bytes;
		if (src_off + size > play->pcm_buffer_size)
			size = play->pcm_buffer_size - src_off;
		if (dst_off + size > capt->pcm_buffer_size)
			size = capt->pcm_buffer_size - dst_off;
		memcpy(dst + dst_off, src + src_off, size);
		capt->silent_size = 0;
		bytes -= size;
		if (!bytes)
			break;
		src_off = (src_off + size) % play->pcm_buffer_size;
		dst_off = (dst_off + size) % capt->pcm_buffer_size;
	}

	if (clear_bytes > 0) {
		clear_capture_buf(capt, clear_bytes);
		capt->silent_size = 0;
	}
}