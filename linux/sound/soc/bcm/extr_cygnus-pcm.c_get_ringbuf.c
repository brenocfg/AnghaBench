#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; } ;
struct ringbuf_regs {int dummy; } ;
struct cygnus_aio_port {struct ringbuf_regs capture_rb_regs; struct ringbuf_regs play_rb_regs; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct cygnus_aio_port* cygnus_dai_get_dma_data (struct snd_pcm_substream*) ; 

__attribute__((used)) static struct ringbuf_regs *get_ringbuf(struct snd_pcm_substream *substream)
{
	struct cygnus_aio_port *aio;
	struct ringbuf_regs *p_rbuf = NULL;

	aio = cygnus_dai_get_dma_data(substream);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		p_rbuf = &aio->play_rb_regs;
	else
		p_rbuf = &aio->capture_rb_regs;

	return p_rbuf;
}