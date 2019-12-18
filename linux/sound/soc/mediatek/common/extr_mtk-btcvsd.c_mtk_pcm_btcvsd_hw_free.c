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
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct mtk_btcvsd_snd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTCVSD_SND_NAME ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  btcvsd_tx_clean_buffer (struct mtk_btcvsd_snd*) ; 
 struct mtk_btcvsd_snd* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_pcm_btcvsd_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, BTCVSD_SND_NAME);
	struct mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		btcvsd_tx_clean_buffer(bt);

	return 0;
}