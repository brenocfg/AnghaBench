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
struct snd_pcm_hw_params {scalar_t__ msbits; } ;
struct au1xpsc_audio_data {scalar_t__ rate; int cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2S_CFG (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  I2S_STAT (struct au1xpsc_audio_data*) ; 
 scalar_t__ PSC_I2SCFG_GET_LEN (int) ; 
 int PSC_I2SCFG_SET_LEN (scalar_t__) ; 
 unsigned long PSC_I2SSTAT_RB ; 
 unsigned long PSC_I2SSTAT_TB ; 
 void* __raw_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 struct au1xpsc_audio_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int au1xpsc_i2s_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);

	int cfgbits;
	unsigned long stat;

	/* check if the PSC is already streaming data */
	stat = __raw_readl(I2S_STAT(pscdata));
	if (stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_RB)) {
		/* reject parameters not currently set up in hardware */
		cfgbits = __raw_readl(I2S_CFG(pscdata));
		if ((PSC_I2SCFG_GET_LEN(cfgbits) != params->msbits) ||
		    (params_rate(params) != pscdata->rate))
			return -EINVAL;
	} else {
		/* set sample bitdepth */
		pscdata->cfg &= ~(0x1f << 4);
		pscdata->cfg |= PSC_I2SCFG_SET_LEN(params->msbits);
		/* remember current rate for other stream */
		pscdata->rate = params_rate(params);
	}
	return 0;
}