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
struct rt5665_priv {struct snd_soc_jack* hs_jack; int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 int RT5665_GP1_PIN_IRQ ; 
 int RT5665_GP1_PIN_MASK ; 
 int /*<<< orphan*/  RT5665_GPIO_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_IRQ_CTRL_1 ; 
#define  RT5665_JD1 129 
#define  RT5665_JD_NULL 128 
 int /*<<< orphan*/  RT5665_PWR_ANLG_2 ; 
 int RT5665_PWR_JD1 ; 
 int /*<<< orphan*/  RT5665_RC_CLK_CTRL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct rt5665_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5665_set_jack_detect(struct snd_soc_component *component,
	struct snd_soc_jack *hs_jack, void *data)
{
	struct rt5665_priv *rt5665 = snd_soc_component_get_drvdata(component);

	switch (rt5665->pdata.jd_src) {
	case RT5665_JD1:
		regmap_update_bits(rt5665->regmap, RT5665_GPIO_CTRL_1,
			RT5665_GP1_PIN_MASK, RT5665_GP1_PIN_IRQ);
		regmap_update_bits(rt5665->regmap, RT5665_RC_CLK_CTRL,
				0xc000, 0xc000);
		regmap_update_bits(rt5665->regmap, RT5665_PWR_ANLG_2,
			RT5665_PWR_JD1, RT5665_PWR_JD1);
		regmap_update_bits(rt5665->regmap, RT5665_IRQ_CTRL_1, 0x8, 0x8);
		break;

	case RT5665_JD_NULL:
		break;

	default:
		dev_warn(component->dev, "Wrong JD source\n");
		break;
	}

	rt5665->hs_jack = hs_jack;

	return 0;
}