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
struct snd_pcm_hw_rule {struct snd_soc_dai* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {struct rsnd_dai_stream capture; struct rsnd_dai_stream playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 struct rsnd_priv* rsnd_rdai_to_priv (struct rsnd_dai*) ; 
 int /*<<< orphan*/  rsnd_runtime_channel_for_ssi_with_params (struct rsnd_dai_stream*,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  rsnd_soc_hw_channels_list ; 
 int rsnd_soc_hw_rule (struct rsnd_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_interval*,struct snd_interval*) ; 

__attribute__((used)) static int __rsnd_soc_hw_rule_channels(struct snd_pcm_hw_params *params,
				       struct snd_pcm_hw_rule *rule,
				       int is_play)
{
	struct snd_interval *ic_ = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval *ir = hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval ic;
	struct snd_soc_dai *dai = rule->private;
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	struct rsnd_priv *priv = rsnd_rdai_to_priv(rdai);
	struct rsnd_dai_stream *io = is_play ? &rdai->playback : &rdai->capture;

	/*
	 * possible sampling rate limitation is same as
	 * 2ch if it supports multi ssi
	 * and same as 8ch if TDM 6ch (see rsnd_ssi_config_init())
	 */
	ic = *ic_;
	ic.min =
	ic.max = rsnd_runtime_channel_for_ssi_with_params(io, params);

	return rsnd_soc_hw_rule(priv, rsnd_soc_hw_channels_list,
				ARRAY_SIZE(rsnd_soc_hw_channels_list),
				ir, &ic);
}