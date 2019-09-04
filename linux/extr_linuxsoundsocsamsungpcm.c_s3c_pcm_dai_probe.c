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
struct snd_soc_dai {int dummy; } ;
struct s3c_pcm_info {int /*<<< orphan*/  dma_capture; int /*<<< orphan*/  dma_playback; } ;

/* Variables and functions */
 struct s3c_pcm_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_pcm_dai_probe(struct snd_soc_dai *dai)
{
	struct s3c_pcm_info *pcm = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, pcm->dma_playback, pcm->dma_capture);

	return 0;
}