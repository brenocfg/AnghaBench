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
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct adav80x {unsigned int* dai_fmt; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ADAV80X_CAPTURE_MODE_I2S ; 
 unsigned int ADAV80X_CAPTURE_MODE_LEFT_J ; 
 unsigned int ADAV80X_CAPTURE_MODE_MASK ; 
 unsigned int ADAV80X_CAPTURE_MODE_MASTER ; 
 unsigned int ADAV80X_CAPTURE_MODE_RIGHT_J ; 
 unsigned int ADAV80X_PLAYBACK_MODE_I2S ; 
 unsigned int ADAV80X_PLAYBACK_MODE_LEFT_J ; 
 unsigned int ADAV80X_PLAYBACK_MODE_MASTER ; 
 unsigned int ADAV80X_PLAYBACK_MODE_RIGHT_J_24 ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/ ** adav80x_port_ctrl_regs ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adav80x_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);
	unsigned int capture = 0x00;
	unsigned int playback = 0x00;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		capture |= ADAV80X_CAPTURE_MODE_MASTER;
		playback |= ADAV80X_PLAYBACK_MODE_MASTER;
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		capture |= ADAV80X_CAPTURE_MODE_I2S;
		playback |= ADAV80X_PLAYBACK_MODE_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		capture |= ADAV80X_CAPTURE_MODE_LEFT_J;
		playback |= ADAV80X_PLAYBACK_MODE_LEFT_J;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		capture |= ADAV80X_CAPTURE_MODE_RIGHT_J;
		playback |= ADAV80X_PLAYBACK_MODE_RIGHT_J_24;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(adav80x->regmap, adav80x_port_ctrl_regs[dai->id][0],
		ADAV80X_CAPTURE_MODE_MASK | ADAV80X_CAPTURE_MODE_MASTER,
		capture);
	regmap_write(adav80x->regmap, adav80x_port_ctrl_regs[dai->id][1],
		playback);

	adav80x->dai_fmt[dai->id] = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	return 0;
}