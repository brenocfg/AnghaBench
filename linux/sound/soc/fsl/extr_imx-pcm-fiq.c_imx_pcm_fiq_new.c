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
struct snd_soc_pcm_runtime {struct snd_pcm* pcm; } ;
struct snd_dma_buffer {scalar_t__ area; } ;
struct snd_pcm_substream {struct snd_dma_buffer dma_buffer; } ;
struct snd_pcm {TYPE_1__* streams; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int imx_pcm_new (struct snd_soc_pcm_runtime*) ; 
 int /*<<< orphan*/  imx_ssi_fiq_end ; 
 unsigned long imx_ssi_fiq_rx_buffer ; 
 int /*<<< orphan*/  imx_ssi_fiq_start ; 
 unsigned long imx_ssi_fiq_tx_buffer ; 
 int /*<<< orphan*/  set_fiq_handler (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int imx_pcm_fiq_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_pcm *pcm = rtd->pcm;
	struct snd_pcm_substream *substream;
	int ret;

	ret = imx_pcm_new(rtd);
	if (ret)
		return ret;

	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	if (substream) {
		struct snd_dma_buffer *buf = &substream->dma_buffer;

		imx_ssi_fiq_tx_buffer = (unsigned long)buf->area;
	}

	substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	if (substream) {
		struct snd_dma_buffer *buf = &substream->dma_buffer;

		imx_ssi_fiq_rx_buffer = (unsigned long)buf->area;
	}

	set_fiq_handler(&imx_ssi_fiq_start,
		&imx_ssi_fiq_end - &imx_ssi_fiq_start);

	return 0;
}