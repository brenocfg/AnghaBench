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
struct xtfpga_i2s {int dummy; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 struct xtfpga_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_set_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*,struct xtfpga_i2s*) ; 

__attribute__((used)) static int xtfpga_i2s_startup(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct xtfpga_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_set_dma_data(dai, substream, i2s);
	return 0;
}