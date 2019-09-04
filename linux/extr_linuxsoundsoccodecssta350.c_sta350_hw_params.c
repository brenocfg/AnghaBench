#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sta350_priv {unsigned int mclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  format; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_3__ {unsigned int fs; int ir; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int EIO ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  STA350_CONFA ; 
 int STA350_CONFA_IR_MASK ; 
 int STA350_CONFA_IR_SHIFT ; 
 int STA350_CONFA_MCS_MASK ; 
 int STA350_CONFA_MCS_SHIFT ; 
 int /*<<< orphan*/  STA350_CONFB ; 
 int STA350_CONFB_SAIFB ; 
 int STA350_CONFB_SAI_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* interpolation_ratios ; 
 unsigned int** mcs_ratio_table ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct sta350_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int sta350_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct sta350_priv *sta350 = snd_soc_component_get_drvdata(component);
	int i, mcs = -EINVAL, ir = -EINVAL;
	unsigned int confa, confb;
	unsigned int rate, ratio;
	int ret;

	if (!sta350->mclk) {
		dev_err(component->dev,
			"sta350->mclk is unset. Unable to determine ratio\n");
		return -EIO;
	}

	rate = params_rate(params);
	ratio = sta350->mclk / rate;
	dev_dbg(component->dev, "rate: %u, ratio: %u\n", rate, ratio);

	for (i = 0; i < ARRAY_SIZE(interpolation_ratios); i++) {
		if (interpolation_ratios[i].fs == rate) {
			ir = interpolation_ratios[i].ir;
			break;
		}
	}

	if (ir < 0) {
		dev_err(component->dev, "Unsupported samplerate: %u\n", rate);
		return -EINVAL;
	}

	for (i = 0; i < 6; i++) {
		if (mcs_ratio_table[ir][i] == ratio) {
			mcs = i;
			break;
		}
	}

	if (mcs < 0) {
		dev_err(component->dev, "Unresolvable ratio: %u\n", ratio);
		return -EINVAL;
	}

	confa = (ir << STA350_CONFA_IR_SHIFT) |
		(mcs << STA350_CONFA_MCS_SHIFT);
	confb = 0;

	switch (params_width(params)) {
	case 24:
		dev_dbg(component->dev, "24bit\n");
		/* fall through */
	case 32:
		dev_dbg(component->dev, "24bit or 32bit\n");
		switch (sta350->format) {
		case SND_SOC_DAIFMT_I2S:
			confb |= 0x0;
			break;
		case SND_SOC_DAIFMT_LEFT_J:
			confb |= 0x1;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0x2;
			break;
		}

		break;
	case 20:
		dev_dbg(component->dev, "20bit\n");
		switch (sta350->format) {
		case SND_SOC_DAIFMT_I2S:
			confb |= 0x4;
			break;
		case SND_SOC_DAIFMT_LEFT_J:
			confb |= 0x5;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0x6;
			break;
		}

		break;
	case 18:
		dev_dbg(component->dev, "18bit\n");
		switch (sta350->format) {
		case SND_SOC_DAIFMT_I2S:
			confb |= 0x8;
			break;
		case SND_SOC_DAIFMT_LEFT_J:
			confb |= 0x9;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0xa;
			break;
		}

		break;
	case 16:
		dev_dbg(component->dev, "16bit\n");
		switch (sta350->format) {
		case SND_SOC_DAIFMT_I2S:
			confb |= 0x0;
			break;
		case SND_SOC_DAIFMT_LEFT_J:
			confb |= 0xd;
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0xe;
			break;
		}

		break;
	default:
		return -EINVAL;
	}

	ret = regmap_update_bits(sta350->regmap, STA350_CONFA,
				 STA350_CONFA_MCS_MASK | STA350_CONFA_IR_MASK,
				 confa);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(sta350->regmap, STA350_CONFB,
				 STA350_CONFB_SAI_MASK | STA350_CONFB_SAIFB,
				 confb);
	if (ret < 0)
		return ret;

	return 0;
}