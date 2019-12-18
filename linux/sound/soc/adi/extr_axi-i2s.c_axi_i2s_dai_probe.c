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
struct axi_i2s {int /*<<< orphan*/  capture_dma_data; scalar_t__ has_capture; int /*<<< orphan*/  playback_dma_data; scalar_t__ has_playback; } ;

/* Variables and functions */
 struct axi_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axi_i2s_dai_probe(struct snd_soc_dai *dai)
{
	struct axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(
		dai,
		i2s->has_playback ? &i2s->playback_dma_data : NULL,
		i2s->has_capture  ? &i2s->capture_dma_data  : NULL);

	return 0;
}