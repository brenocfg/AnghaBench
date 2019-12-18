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
struct snd_soc_component {int dummy; } ;
struct rt5631_priv {int codec_version; scalar_t__ dmic_used_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5631_ADDA_MIXER_INTL_REG3 ; 
 int /*<<< orphan*/  RT5631_DIG_MIC_CTRL ; 
 int RT5631_DMIC_L_CH_LATCH_FALLING ; 
 int RT5631_DMIC_L_CH_LATCH_MASK ; 
 int RT5631_DMIC_R_CH_LATCH_MASK ; 
 int RT5631_DMIC_R_CH_LATCH_RISING ; 
 int /*<<< orphan*/  RT5631_GPIO_CTRL ; 
 int RT5631_GPIO_DMIC_FUN_SEL_DIMC ; 
 int RT5631_GPIO_DMIC_FUN_SEL_MASK ; 
 int RT5631_GPIO_PIN_FUN_SEL_GPIO_DIMC ; 
 int RT5631_GPIO_PIN_FUN_SEL_MASK ; 
 int /*<<< orphan*/  RT5631_INT_ST_IRQ_CTRL_2 ; 
 int RT5631_PWR_FAST_VREF_CTRL ; 
 int RT5631_PWR_MAIN_BIAS ; 
 int /*<<< orphan*/  RT5631_PWR_MANAG_ADD3 ; 
 int RT5631_PWR_VREF ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int rt5631_read_index (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5631_reset (struct snd_soc_component*) ; 
 struct rt5631_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_init_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt5631_probe(struct snd_soc_component *component)
{
	struct rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	val = rt5631_read_index(component, RT5631_ADDA_MIXER_INTL_REG3);
	if (val & 0x0002)
		rt5631->codec_version = 1;
	else
		rt5631->codec_version = 0;

	rt5631_reset(component);
	snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
		RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS,
		RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS);
	msleep(80);
	snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
		RT5631_PWR_FAST_VREF_CTRL, RT5631_PWR_FAST_VREF_CTRL);
	/* enable HP zero cross */
	snd_soc_component_write(component, RT5631_INT_ST_IRQ_CTRL_2, 0x0f18);
	/* power off ClassD auto Recovery */
	if (rt5631->codec_version)
		snd_soc_component_update_bits(component, RT5631_INT_ST_IRQ_CTRL_2,
					0x2000, 0x2000);
	else
		snd_soc_component_update_bits(component, RT5631_INT_ST_IRQ_CTRL_2,
					0x2000, 0);
	/* DMIC */
	if (rt5631->dmic_used_flag) {
		snd_soc_component_update_bits(component, RT5631_GPIO_CTRL,
			RT5631_GPIO_PIN_FUN_SEL_MASK |
			RT5631_GPIO_DMIC_FUN_SEL_MASK,
			RT5631_GPIO_PIN_FUN_SEL_GPIO_DIMC |
			RT5631_GPIO_DMIC_FUN_SEL_DIMC);
		snd_soc_component_update_bits(component, RT5631_DIG_MIC_CTRL,
			RT5631_DMIC_L_CH_LATCH_MASK |
			RT5631_DMIC_R_CH_LATCH_MASK,
			RT5631_DMIC_L_CH_LATCH_FALLING |
			RT5631_DMIC_R_CH_LATCH_RISING);
	}

	snd_soc_component_init_bias_level(component, SND_SOC_BIAS_STANDBY);

	return 0;
}