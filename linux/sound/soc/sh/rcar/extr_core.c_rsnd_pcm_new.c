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
struct snd_soc_dai {int dummy; } ;
struct rsnd_dai {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  pcm_new ; 
 int rsnd_dai_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_soc_pcm_runtime*) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 int rsnd_preallocate_pages (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsnd_pcm_new(struct snd_soc_pcm_runtime *rtd,
			struct snd_soc_dai *dai)
{
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	int ret;

	ret = rsnd_dai_call(pcm_new, &rdai->playback, rtd);
	if (ret)
		return ret;

	ret = rsnd_dai_call(pcm_new, &rdai->capture, rtd);
	if (ret)
		return ret;

	ret = rsnd_preallocate_pages(rtd, &rdai->playback,
				     SNDRV_PCM_STREAM_PLAYBACK);
	if (ret)
		return ret;

	ret = rsnd_preallocate_pages(rtd, &rdai->capture,
				     SNDRV_PCM_STREAM_CAPTURE);
	if (ret)
		return ret;

	return 0;
}