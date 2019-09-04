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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4671_BCKP ; 
 int /*<<< orphan*/  AK4671_DIF ; 
 int /*<<< orphan*/  AK4671_DIF_DSP_MODE ; 
 int /*<<< orphan*/  AK4671_DIF_I2S_MODE ; 
 int /*<<< orphan*/  AK4671_DIF_MSB_MODE ; 
 int /*<<< orphan*/  AK4671_FORMAT_SELECT ; 
 int /*<<< orphan*/  AK4671_MSBS ; 
 int /*<<< orphan*/  AK4671_M_S ; 
 int /*<<< orphan*/  AK4671_PLL_MODE_SELECT1 ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBM_CFS 131 
#define  SND_SOC_DAIFMT_DSP_A 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak4671_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	u8 mode;
	u8 format;

	/* set master/slave audio interface */
	mode = snd_soc_component_read32(component, AK4671_PLL_MODE_SELECT1);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		mode |= AK4671_M_S;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		mode &= ~(AK4671_M_S);
		break;
	default:
		return -EINVAL;
	}

	/* interface format */
	format = snd_soc_component_read32(component, AK4671_FORMAT_SELECT);
	format &= ~AK4671_DIF;

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		format |= AK4671_DIF_I2S_MODE;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		format |= AK4671_DIF_MSB_MODE;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		format |= AK4671_DIF_DSP_MODE;
		format |= AK4671_BCKP;
		format |= AK4671_MSBS;
		break;
	default:
		return -EINVAL;
	}

	/* set mode and format */
	snd_soc_component_write(component, AK4671_PLL_MODE_SELECT1, mode);
	snd_soc_component_write(component, AK4671_FORMAT_SELECT, format);

	return 0;
}