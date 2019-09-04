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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct fsl_sai {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_SAI_CR3_TRCE ; 
 int /*<<< orphan*/  FSL_SAI_xCR3 (int) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void fsl_sai_shutdown(struct snd_pcm_substream *substream,
		struct snd_soc_dai *cpu_dai)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	regmap_update_bits(sai->regmap, FSL_SAI_xCR3(tx), FSL_SAI_CR3_TRCE, 0);

	clk_disable_unprepare(sai->bus_clk);
}