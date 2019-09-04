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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct cs35l33_private {int /*<<< orphan*/  regmap; scalar_t__ is_tdm_mode; int /*<<< orphan*/  mclk_int; } ;
struct TYPE_2__ {int int_fs_ratio; int adsp_rate; } ;

/* Variables and functions */
 int CS35L33_ADSP_FS ; 
 int CS35L33_AUDIN_RX_DEPTH ; 
 int CS35L33_AUDIN_RX_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L33_CLK_CTL ; 
 int CS35L33_INT_FS_RATE ; 
 int /*<<< orphan*/  CS35L33_RX_AUD ; 
 int cs35l33_get_mclk_coeff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cs35l33_mclk_coeffs ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l33_pcm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);
	int sample_size = params_width(params);
	int coeff = cs35l33_get_mclk_coeff(priv->mclk_int, params_rate(params));

	if (coeff < 0)
		return coeff;

	regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
		CS35L33_ADSP_FS | CS35L33_INT_FS_RATE,
		cs35l33_mclk_coeffs[coeff].int_fs_ratio
		| cs35l33_mclk_coeffs[coeff].adsp_rate);

	if (priv->is_tdm_mode) {
		sample_size = (sample_size / 8) - 1;
		if (sample_size > 2)
			sample_size = 2;
		regmap_update_bits(priv->regmap, CS35L33_RX_AUD,
			CS35L33_AUDIN_RX_DEPTH,
			sample_size << CS35L33_AUDIN_RX_DEPTH_SHIFT);
	}

	dev_dbg(component->dev, "sample rate=%d, bits per sample=%d\n",
		params_rate(params), params_width(params));

	return 0;
}