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
struct snd_soc_dai {scalar_t__ active; } ;
struct snd_pcm_substream {int dummy; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_TOP_CON0 ; 
 int AUD_TCON0_PDN_22M ; 
 int AUD_TCON0_PDN_24M ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt8173_afe_i2s_startup(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	if (dai->active)
		return 0;

	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0,
			   AUD_TCON0_PDN_22M | AUD_TCON0_PDN_24M, 0);
	return 0;
}