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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int regvalue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5632_DAC_CLK_CTRL1 ; 
 int /*<<< orphan*/  ALC5632_DAI_CONTROL ; 
 int ALC5632_DAI_I2S_DL_16 ; 
 int ALC5632_DAI_I2S_DL_20 ; 
 int ALC5632_DAI_I2S_DL_24 ; 
 int ALC5632_DAI_I2S_DL_MASK ; 
 int EINVAL ; 
 TYPE_1__* coeff_div ; 
 int get_coeff (struct snd_soc_component*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alc5632_pcm_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	int coeff, rate;
	u16 iface;

	iface = snd_soc_component_read32(component, ALC5632_DAI_CONTROL);
	iface &= ~ALC5632_DAI_I2S_DL_MASK;

	/* bit size */
	switch (params_width(params)) {
	case 16:
		iface |= ALC5632_DAI_I2S_DL_16;
		break;
	case 20:
		iface |= ALC5632_DAI_I2S_DL_20;
		break;
	case 24:
		iface |= ALC5632_DAI_I2S_DL_24;
		break;
	default:
		return -EINVAL;
	}

	/* set iface & srate */
	snd_soc_component_write(component, ALC5632_DAI_CONTROL, iface);
	rate = params_rate(params);
	coeff = get_coeff(component, rate);
	if (coeff < 0)
		return -EINVAL;

	coeff = coeff_div[coeff].regvalue;
	snd_soc_component_write(component, ALC5632_DAC_CLK_CTRL1, coeff);

	return 0;
}