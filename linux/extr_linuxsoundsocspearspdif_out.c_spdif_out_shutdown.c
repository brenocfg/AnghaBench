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
struct spdif_out_dev {int running; int /*<<< orphan*/  clk; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct spdif_out_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void spdif_out_shutdown(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct spdif_out_dev *host = snd_soc_dai_get_drvdata(dai);

	if (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		return;

	clk_disable(host->clk);
	host->running = false;
}