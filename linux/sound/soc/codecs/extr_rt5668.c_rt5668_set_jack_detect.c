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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int jd_src; } ;
struct rt5668_priv {struct snd_soc_jack* hs_jack; int /*<<< orphan*/  regmap; int /*<<< orphan*/  jack_detect_work; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5668_CBJ_CTRL_1 ; 
 int /*<<< orphan*/  RT5668_CBJ_CTRL_2 ; 
 int /*<<< orphan*/  RT5668_CBJ_CTRL_3 ; 
 int /*<<< orphan*/  RT5668_CBJ_IN_BUF_EN ; 
 int /*<<< orphan*/  RT5668_EXT_JD_SRC ; 
 int /*<<< orphan*/  RT5668_EXT_JD_SRC_MANUAL ; 
 int RT5668_GP1_PIN_IRQ ; 
 int RT5668_GP1_PIN_MASK ; 
 int /*<<< orphan*/  RT5668_GPIO_CTRL_1 ; 
 int /*<<< orphan*/  RT5668_IRQ_CTRL_2 ; 
#define  RT5668_JD1 129 
 int RT5668_JD1_DIS ; 
 int RT5668_JD1_EN ; 
 int RT5668_JD1_EN_MASK ; 
 int RT5668_JD1_POL_MASK ; 
 int RT5668_JD1_POL_NOR ; 
#define  RT5668_JD_NULL 128 
 int RT5668_POW_ANA ; 
 int RT5668_POW_IRQ ; 
 int RT5668_POW_JDH ; 
 int RT5668_POW_JDL ; 
 int /*<<< orphan*/  RT5668_PWR_ANLG_2 ; 
 int RT5668_PWR_JDH ; 
 int RT5668_PWR_JDL ; 
 int /*<<< orphan*/  RT5668_RC_CLK_CTRL ; 
 int /*<<< orphan*/  RT5668_SAR_IL_CMD_1 ; 
 int /*<<< orphan*/  RT5668_SAR_POW_EN ; 
 int /*<<< orphan*/  RT5668_SAR_POW_MASK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct rt5668_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int rt5668_set_jack_detect(struct snd_soc_component *component,
	struct snd_soc_jack *hs_jack, void *data)
{
	struct rt5668_priv *rt5668 = snd_soc_component_get_drvdata(component);

	switch (rt5668->pdata.jd_src) {
	case RT5668_JD1:
		snd_soc_component_update_bits(component, RT5668_CBJ_CTRL_2,
			RT5668_EXT_JD_SRC, RT5668_EXT_JD_SRC_MANUAL);
		snd_soc_component_write(component, RT5668_CBJ_CTRL_1, 0xd002);
		snd_soc_component_update_bits(component, RT5668_CBJ_CTRL_3,
			RT5668_CBJ_IN_BUF_EN, RT5668_CBJ_IN_BUF_EN);
		snd_soc_component_update_bits(component, RT5668_SAR_IL_CMD_1,
			RT5668_SAR_POW_MASK, RT5668_SAR_POW_EN);
		regmap_update_bits(rt5668->regmap, RT5668_GPIO_CTRL_1,
			RT5668_GP1_PIN_MASK, RT5668_GP1_PIN_IRQ);
		regmap_update_bits(rt5668->regmap, RT5668_RC_CLK_CTRL,
				RT5668_POW_IRQ | RT5668_POW_JDH |
				RT5668_POW_ANA, RT5668_POW_IRQ |
				RT5668_POW_JDH | RT5668_POW_ANA);
		regmap_update_bits(rt5668->regmap, RT5668_PWR_ANLG_2,
			RT5668_PWR_JDH | RT5668_PWR_JDL,
			RT5668_PWR_JDH | RT5668_PWR_JDL);
		regmap_update_bits(rt5668->regmap, RT5668_IRQ_CTRL_2,
			RT5668_JD1_EN_MASK | RT5668_JD1_POL_MASK,
			RT5668_JD1_EN | RT5668_JD1_POL_NOR);
		mod_delayed_work(system_power_efficient_wq,
			   &rt5668->jack_detect_work, msecs_to_jiffies(250));
		break;

	case RT5668_JD_NULL:
		regmap_update_bits(rt5668->regmap, RT5668_IRQ_CTRL_2,
			RT5668_JD1_EN_MASK, RT5668_JD1_DIS);
		regmap_update_bits(rt5668->regmap, RT5668_RC_CLK_CTRL,
				RT5668_POW_JDH | RT5668_POW_JDL, 0);
		break;

	default:
		dev_warn(component->dev, "Wrong JD source\n");
		break;
	}

	rt5668->hs_jack = hs_jack;

	return 0;
}