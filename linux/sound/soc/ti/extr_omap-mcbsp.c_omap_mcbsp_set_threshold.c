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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct omap_mcbsp {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ buffer_size; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  omap_mcbsp_set_rx_threshold (struct omap_mcbsp*,int) ; 
 int /*<<< orphan*/  omap_mcbsp_set_tx_threshold (struct omap_mcbsp*,int) ; 
 struct omap_mcbsp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void omap_mcbsp_set_threshold(struct snd_pcm_substream *substream,
		unsigned int packet_size)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	int words;

	/* No need to proceed further if McBSP does not have FIFO */
	if (mcbsp->pdata->buffer_size == 0)
		return;

	/*
	 * Configure McBSP threshold based on either:
	 * packet_size, when the sDMA is in packet mode, or based on the
	 * period size in THRESHOLD mode, otherwise use McBSP threshold = 1
	 * for mono streams.
	 */
	if (packet_size)
		words = packet_size;
	else
		words = 1;

	/* Configure McBSP internal buffer usage */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		omap_mcbsp_set_tx_threshold(mcbsp, words);
	else
		omap_mcbsp_set_rx_threshold(mcbsp, words);
}