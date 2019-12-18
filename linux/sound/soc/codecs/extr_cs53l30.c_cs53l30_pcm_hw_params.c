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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs53l30_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  mclk_rate; } ;
struct TYPE_2__ {int /*<<< orphan*/  asp_rate; int /*<<< orphan*/  mclk_int_scale; int /*<<< orphan*/  internal_fs_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS53L30_ASPCFG_CTL ; 
 int /*<<< orphan*/  CS53L30_ASP_RATE_MASK ; 
 int /*<<< orphan*/  CS53L30_INTRNL_FS_RATIO_MASK ; 
 int /*<<< orphan*/  CS53L30_INT_SR_CTL ; 
 int /*<<< orphan*/  CS53L30_MCLKCTL ; 
 int /*<<< orphan*/  CS53L30_MCLK_INT_SCALE_MASK ; 
 int EINVAL ; 
 int cs53l30_get_mclk_coeff (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cs53l30_mclk_coeffs ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs53l30_private* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs53l30_pcm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct cs53l30_private *priv = snd_soc_component_get_drvdata(dai->component);
	int srate = params_rate(params);
	int mclk_coeff;

	/* MCLK -> srate */
	mclk_coeff = cs53l30_get_mclk_coeff(priv->mclk_rate, srate);
	if (mclk_coeff < 0)
		return -EINVAL;

	regmap_update_bits(priv->regmap, CS53L30_INT_SR_CTL,
			   CS53L30_INTRNL_FS_RATIO_MASK,
			   cs53l30_mclk_coeffs[mclk_coeff].internal_fs_ratio);

	regmap_update_bits(priv->regmap, CS53L30_MCLKCTL,
			   CS53L30_MCLK_INT_SCALE_MASK,
			   cs53l30_mclk_coeffs[mclk_coeff].mclk_int_scale);

	regmap_update_bits(priv->regmap, CS53L30_ASPCFG_CTL,
			   CS53L30_ASP_RATE_MASK,
			   cs53l30_mclk_coeffs[mclk_coeff].asp_rate);

	return 0;
}