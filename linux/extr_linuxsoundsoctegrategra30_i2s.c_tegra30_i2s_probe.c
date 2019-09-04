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
struct tegra30_i2s {int /*<<< orphan*/  playback_dma_data; int /*<<< orphan*/  capture_dma_data; } ;
struct snd_soc_dai {int /*<<< orphan*/ * playback_dma_data; int /*<<< orphan*/ * capture_dma_data; } ;

/* Variables and functions */
 struct tegra30_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int tegra30_i2s_probe(struct snd_soc_dai *dai)
{
	struct tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = &i2s->capture_dma_data;
	dai->playback_dma_data = &i2s->playback_dma_data;

	return 0;
}