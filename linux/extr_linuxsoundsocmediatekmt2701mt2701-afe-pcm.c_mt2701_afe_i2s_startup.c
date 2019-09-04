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
struct snd_soc_dai {int /*<<< orphan*/  id; } ;
struct snd_pcm_substream {int dummy; } ;
struct mtk_base_afe {struct mt2701_afe_private* platform_priv; } ;
struct mt2701_afe_private {TYPE_1__* soc; } ;
struct TYPE_2__ {int has_one_heart_mode; } ;

/* Variables and functions */
 int mt2701_afe_enable_mclk (struct mtk_base_afe*,int) ; 
 int mt2701_dai_num_to_i2s (struct mtk_base_afe*,int /*<<< orphan*/ ) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt2701_afe_i2s_startup(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	struct mt2701_afe_private *afe_priv = afe->platform_priv;
	int i2s_num = mt2701_dai_num_to_i2s(afe, dai->id);
	bool mode = afe_priv->soc->has_one_heart_mode;

	if (i2s_num < 0)
		return i2s_num;

	return mt2701_afe_enable_mclk(afe, mode ? 1 : i2s_num);
}