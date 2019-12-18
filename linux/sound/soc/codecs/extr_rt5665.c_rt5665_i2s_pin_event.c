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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 unsigned int RT5665_GP2_PIN_BCLK2 ; 
 unsigned int RT5665_GP2_PIN_MASK ; 
 unsigned int RT5665_GP3_PIN_LRCK2 ; 
 unsigned int RT5665_GP3_PIN_MASK ; 
 unsigned int RT5665_GP4_PIN_DACDAT2_1 ; 
 unsigned int RT5665_GP4_PIN_MASK ; 
 unsigned int RT5665_GP5_PIN_ADCDAT2_1 ; 
 unsigned int RT5665_GP5_PIN_MASK ; 
 unsigned int RT5665_GP6_PIN_BCLK3 ; 
 unsigned int RT5665_GP6_PIN_MASK ; 
 unsigned int RT5665_GP7_PIN_LRCK3 ; 
 unsigned int RT5665_GP7_PIN_MASK ; 
 unsigned int RT5665_GP8_PIN_DACDAT2_2 ; 
 unsigned int RT5665_GP8_PIN_DACDAT3 ; 
 unsigned int RT5665_GP8_PIN_MASK ; 
 unsigned int RT5665_GP9_PIN_ADCDAT2_2 ; 
 unsigned int RT5665_GP9_PIN_ADCDAT3 ; 
 unsigned int RT5665_GP9_PIN_MASK ; 
 int /*<<< orphan*/  RT5665_GPIO_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_GPIO_CTRL_2 ; 
#define  RT5665_PWR_I2S2_1_BIT 132 
#define  RT5665_PWR_I2S2_2_BIT 131 
#define  RT5665_PWR_I2S3_BIT 130 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5665_i2s_pin_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int val1, val2, mask1 = 0, mask2 = 0;

	switch (w->shift) {
	case RT5665_PWR_I2S2_1_BIT:
		mask1 = RT5665_GP2_PIN_MASK | RT5665_GP3_PIN_MASK |
			RT5665_GP4_PIN_MASK | RT5665_GP5_PIN_MASK;
		val1 = RT5665_GP2_PIN_BCLK2 | RT5665_GP3_PIN_LRCK2 |
			RT5665_GP4_PIN_DACDAT2_1 | RT5665_GP5_PIN_ADCDAT2_1;
		break;
	case RT5665_PWR_I2S2_2_BIT:
		mask1 = RT5665_GP2_PIN_MASK | RT5665_GP3_PIN_MASK |
			RT5665_GP8_PIN_MASK;
		val1 = RT5665_GP2_PIN_BCLK2 | RT5665_GP3_PIN_LRCK2 |
			RT5665_GP8_PIN_DACDAT2_2;
		mask2 = RT5665_GP9_PIN_MASK;
		val2 = RT5665_GP9_PIN_ADCDAT2_2;
		break;
	case RT5665_PWR_I2S3_BIT:
		mask1 = RT5665_GP6_PIN_MASK | RT5665_GP7_PIN_MASK |
			RT5665_GP8_PIN_MASK;
		val1 = RT5665_GP6_PIN_BCLK3 | RT5665_GP7_PIN_LRCK3 |
			RT5665_GP8_PIN_DACDAT3;
		mask2 = RT5665_GP9_PIN_MASK;
		val2 = RT5665_GP9_PIN_ADCDAT3;
		break;
	}
	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (mask1)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_1,
					    mask1, val1);
		if (mask2)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_2,
					    mask2, val2);
		break;
	case SND_SOC_DAPM_POST_PMD:
		if (mask1)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_1,
					    mask1, 0);
		if (mask2)
			snd_soc_component_update_bits(component, RT5665_GPIO_CTRL_2,
					    mask2, 0);
		break;
	default:
		return 0;
	}

	return 0;
}