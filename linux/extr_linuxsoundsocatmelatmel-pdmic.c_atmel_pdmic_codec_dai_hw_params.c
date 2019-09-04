#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_2__* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct atmel_pdmic {int /*<<< orphan*/  gclk; int /*<<< orphan*/  pclk; } ;
struct TYPE_3__ {unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PDMIC_DSPR0 ; 
 int PDMIC_DSPR0_OSR_128 ; 
 int PDMIC_DSPR0_OSR_64 ; 
 int PDMIC_DSPR0_OSR_MASK ; 
 int PDMIC_DSPR0_OSR_SHIFT ; 
 int PDMIC_DSPR0_SIZE_16_BITS ; 
 int PDMIC_DSPR0_SIZE_32_BITS ; 
 int PDMIC_DSPR0_SIZE_MASK ; 
 int PDMIC_DSPR0_SIZE_SHIFT ; 
 int /*<<< orphan*/  PDMIC_MR ; 
 int PDMIC_MR_CLKS_GCK ; 
 int PDMIC_MR_CLKS_MASK ; 
 int PDMIC_MR_CLKS_PCK ; 
 int PDMIC_MR_CLKS_SHIFT ; 
 int PDMIC_MR_PRESCAL_MASK ; 
 int PDMIC_MR_PRESCAL_MAX_VAL ; 
 int PDMIC_MR_PRESCAL_SHIFT ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct atmel_pdmic* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
atmel_pdmic_codec_dai_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *codec_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct atmel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_component *component = codec_dai->component;
	unsigned int rate_min = substream->runtime->hw.rate_min;
	unsigned int rate_max = substream->runtime->hw.rate_max;
	int fs = params_rate(params);
	int bits = params_width(params);
	unsigned long pclk_rate, gclk_rate;
	unsigned int f_pdmic;
	u32 mr_val, dspr0_val, pclk_prescal, gclk_prescal;

	if (params_channels(params) != 1) {
		dev_err(component->dev,
			"only supports one channel\n");
		return -EINVAL;
	}

	if ((fs < rate_min) || (fs > rate_max)) {
		dev_err(component->dev,
			"sample rate is %dHz, min rate is %dHz, max rate is %dHz\n",
			fs, rate_min, rate_max);

		return -EINVAL;
	}

	switch (bits) {
	case 16:
		dspr0_val = (PDMIC_DSPR0_SIZE_16_BITS
			     << PDMIC_DSPR0_SIZE_SHIFT);
		break;
	case 32:
		dspr0_val = (PDMIC_DSPR0_SIZE_32_BITS
			     << PDMIC_DSPR0_SIZE_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	if ((fs << 7) > (rate_max << 6)) {
		f_pdmic = fs << 6;
		dspr0_val |= PDMIC_DSPR0_OSR_64 << PDMIC_DSPR0_OSR_SHIFT;
	} else {
		f_pdmic = fs << 7;
		dspr0_val |= PDMIC_DSPR0_OSR_128 << PDMIC_DSPR0_OSR_SHIFT;
	}

	pclk_rate = clk_get_rate(dd->pclk);
	gclk_rate = clk_get_rate(dd->gclk);

	/* PRESCAL = SELCK/(2*f_pdmic) - 1*/
	pclk_prescal = (u32)(pclk_rate/(f_pdmic << 1)) - 1;
	gclk_prescal = (u32)(gclk_rate/(f_pdmic << 1)) - 1;

	if ((pclk_prescal > PDMIC_MR_PRESCAL_MAX_VAL) ||
	    (gclk_rate/((gclk_prescal + 1) << 1) <
	     pclk_rate/((pclk_prescal + 1) << 1))) {
		mr_val = gclk_prescal << PDMIC_MR_PRESCAL_SHIFT;
		mr_val |= PDMIC_MR_CLKS_GCK << PDMIC_MR_CLKS_SHIFT;
	} else {
		mr_val = pclk_prescal << PDMIC_MR_PRESCAL_SHIFT;
		mr_val |= PDMIC_MR_CLKS_PCK << PDMIC_MR_CLKS_SHIFT;
	}

	snd_soc_component_update_bits(component, PDMIC_MR,
		PDMIC_MR_PRESCAL_MASK | PDMIC_MR_CLKS_MASK, mr_val);

	snd_soc_component_update_bits(component, PDMIC_DSPR0,
		PDMIC_DSPR0_OSR_MASK | PDMIC_DSPR0_SIZE_MASK, dspr0_val);

	return 0;
}