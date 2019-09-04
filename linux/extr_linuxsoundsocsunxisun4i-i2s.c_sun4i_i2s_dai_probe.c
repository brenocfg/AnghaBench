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
struct sun4i_i2s {int /*<<< orphan*/  capture_dma_data; int /*<<< orphan*/  playback_dma_data; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 struct sun4i_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct sun4i_i2s*) ; 

__attribute__((used)) static int sun4i_i2s_dai_probe(struct snd_soc_dai *dai)
{
	struct sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai,
				  &i2s->playback_dma_data,
				  &i2s->capture_dma_data);

	snd_soc_dai_set_drvdata(dai, i2s);

	return 0;
}