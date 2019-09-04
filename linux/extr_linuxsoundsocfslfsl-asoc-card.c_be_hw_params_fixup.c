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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct snd_interval {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
struct fsl_asoc_card_priv {int /*<<< orphan*/  asrc_format; int /*<<< orphan*/  asrc_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_set_format (struct snd_mask*,int /*<<< orphan*/ ) ; 
 struct fsl_asoc_card_priv* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_hw_params_fixup(struct snd_soc_pcm_runtime *rtd,
			      struct snd_pcm_hw_params *params)
{
	struct fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	struct snd_interval *rate;
	struct snd_mask *mask;

	rate = hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	rate->max = rate->min = priv->asrc_rate;

	mask = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	snd_mask_none(mask);
	snd_mask_set_format(mask, priv->asrc_format);

	return 0;
}