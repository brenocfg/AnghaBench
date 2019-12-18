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
typedef  int u32 ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct ringbuf_regs {scalar_t__ rdaddr; scalar_t__ wraddr; } ;
struct cygnus_aio_port {TYPE_1__* cygaud; } ;
struct TYPE_2__ {scalar_t__ audio; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct cygnus_aio_port* cygnus_dai_get_dma_data (struct snd_pcm_substream*) ; 
 struct ringbuf_regs* get_ringbuf (struct snd_pcm_substream*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cygnus_pcm_period_elapsed(struct snd_pcm_substream *substream)
{
	struct cygnus_aio_port *aio;
	struct ringbuf_regs *p_rbuf = NULL;
	u32 regval;

	aio = cygnus_dai_get_dma_data(substream);

	p_rbuf = get_ringbuf(substream);

	/*
	 * If free/full mark interrupt occurs, provide timestamp
	 * to ALSA and update appropriate idx by period_bytes
	 */
	snd_pcm_period_elapsed(substream);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/* Set the ring buffer to full */
		regval = readl(aio->cygaud->audio + p_rbuf->rdaddr);
		regval = regval ^ BIT(31);
		writel(regval, aio->cygaud->audio + p_rbuf->wraddr);
	} else {
		/* Set the ring buffer to empty */
		regval = readl(aio->cygaud->audio + p_rbuf->wraddr);
		writel(regval, aio->cygaud->audio + p_rbuf->rdaddr);
	}
}