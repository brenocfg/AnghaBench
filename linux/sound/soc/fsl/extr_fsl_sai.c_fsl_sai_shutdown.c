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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct fsl_sai {int /*<<< orphan*/  regmap; TYPE_1__* soc_data; } ;
struct TYPE_2__ {unsigned int reg_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_SAI_CR3_TRCE_MASK ; 
 int /*<<< orphan*/  FSL_SAI_xCR3 (int,unsigned int) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void fsl_sai_shutdown(struct snd_pcm_substream *substream,
		struct snd_soc_dai *cpu_dai)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned int ofs = sai->soc_data->reg_offset;
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	regmap_update_bits(sai->regmap, FSL_SAI_xCR3(tx, ofs),
			   FSL_SAI_CR3_TRCE_MASK, 0);
}