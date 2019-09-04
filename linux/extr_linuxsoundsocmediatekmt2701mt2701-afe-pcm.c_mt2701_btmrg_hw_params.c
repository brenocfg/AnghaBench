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
typedef  int u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct mtk_base_afe {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_DAIBT_CON0 ; 
 int AFE_DAIBT_CON0_BT_FUNC_EN ; 
 int AFE_DAIBT_CON0_BT_FUNC_RDY ; 
 int AFE_DAIBT_CON0_BT_WIDE_MODE_EN ; 
 int AFE_DAIBT_CON0_DAIBT_EN ; 
 int AFE_DAIBT_CON0_MRG_USE ; 
 int /*<<< orphan*/  AFE_MRGIF_CON ; 
 int AFE_MRGIF_CON_I2S_MODE_32K ; 
 int AFE_MRGIF_CON_I2S_MODE_MASK ; 
 int AFE_MRGIF_CON_MRG_EN ; 
 int AFE_MRGIF_CON_MRG_I2S_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mtk_base_afe* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mt2701_btmrg_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	int stream_fs;
	u32 val, msk;

	stream_fs = params_rate(params);

	if (stream_fs != 8000 && stream_fs != 16000) {
		dev_err(afe->dev, "unsupported rate %d\n", stream_fs);
		return -EINVAL;
	}

	regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
			   AFE_MRGIF_CON_I2S_MODE_MASK,
			   AFE_MRGIF_CON_I2S_MODE_32K);

	val = AFE_DAIBT_CON0_BT_FUNC_EN | AFE_DAIBT_CON0_BT_FUNC_RDY
	      | AFE_DAIBT_CON0_MRG_USE;
	msk = val;

	if (stream_fs == 16000)
		val |= AFE_DAIBT_CON0_BT_WIDE_MODE_EN;

	msk |= AFE_DAIBT_CON0_BT_WIDE_MODE_EN;

	regmap_update_bits(afe->regmap, AFE_DAIBT_CON0, msk, val);

	regmap_update_bits(afe->regmap, AFE_DAIBT_CON0,
			   AFE_DAIBT_CON0_DAIBT_EN,
			   AFE_DAIBT_CON0_DAIBT_EN);
	regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
			   AFE_MRGIF_CON_MRG_I2S_EN,
			   AFE_MRGIF_CON_MRG_I2S_EN);
	regmap_update_bits(afe->regmap, AFE_MRGIF_CON,
			   AFE_MRGIF_CON_MRG_EN,
			   AFE_MRGIF_CON_MRG_EN);
	return 0;
}