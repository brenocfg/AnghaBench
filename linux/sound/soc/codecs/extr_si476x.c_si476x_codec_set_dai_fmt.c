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
typedef  int u16 ;
struct snd_soc_dai {TYPE_1__* component; int /*<<< orphan*/  dev; } ;
struct si476x_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SI476X_DAUDIO_MODE_DSP_A ; 
 int SI476X_DAUDIO_MODE_DSP_B ; 
 int SI476X_DAUDIO_MODE_I2S ; 
 int SI476X_DAUDIO_MODE_IB ; 
 int SI476X_DAUDIO_MODE_IF ; 
 int SI476X_DAUDIO_MODE_LEFT_J ; 
 int SI476X_DAUDIO_MODE_RIGHT_J ; 
 int /*<<< orphan*/  SI476X_DIGITAL_IO_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  SI476X_DIGITAL_IO_OUTPUT_FORMAT_MASK ; 
 unsigned int SND_SOC_DAIFMT_CBS_CFS ; 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct si476x_core* i2c_mfd_cell_to_core (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si476x_core_lock (struct si476x_core*) ; 
 int /*<<< orphan*/  si476x_core_unlock (struct si476x_core*) ; 
 int snd_soc_component_update_bits (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si476x_codec_set_dai_fmt(struct snd_soc_dai *codec_dai,
				    unsigned int fmt)
{
	struct si476x_core *core = i2c_mfd_cell_to_core(codec_dai->dev);
	int err;
	u16 format = 0;

	if ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		return -EINVAL;

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		format |= SI476X_DAUDIO_MODE_DSP_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		format |= SI476X_DAUDIO_MODE_DSP_B;
		break;
	case SND_SOC_DAIFMT_I2S:
		format |= SI476X_DAUDIO_MODE_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		format |= SI476X_DAUDIO_MODE_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		format |= SI476X_DAUDIO_MODE_LEFT_J;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_NF:
			format |= SI476X_DAUDIO_MODE_IB;
			break;
		default:
			return -EINVAL;
		}
		break;
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_IF:
			format |= SI476X_DAUDIO_MODE_IB |
				SI476X_DAUDIO_MODE_IF;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			format |= SI476X_DAUDIO_MODE_IB;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			format |= SI476X_DAUDIO_MODE_IF;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	si476x_core_lock(core);

	err = snd_soc_component_update_bits(codec_dai->component, SI476X_DIGITAL_IO_OUTPUT_FORMAT,
				  SI476X_DIGITAL_IO_OUTPUT_FORMAT_MASK,
				  format);

	si476x_core_unlock(core);

	if (err < 0) {
		dev_err(codec_dai->component->dev, "Failed to set output format\n");
		return err;
	}

	return 0;
}