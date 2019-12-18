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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int /*<<< orphan*/  msbits; } ;
struct au1xpsc_audio_data {unsigned long cfg; } ;

/* Variables and functions */
 unsigned long CFG_SZ_MASK ; 
 int EINVAL ; 
 unsigned long msbits_to_reg (int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int au1xi2s_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct au1xpsc_audio_data *ctx = snd_soc_dai_get_drvdata(dai);
	unsigned long v;

	v = msbits_to_reg(params->msbits);
	if (!v)
		return -EINVAL;

	ctx->cfg &= ~CFG_SZ_MASK;
	ctx->cfg |= v;
	return 0;
}