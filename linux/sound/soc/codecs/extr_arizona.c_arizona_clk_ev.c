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
struct snd_soc_dapm_widget {int /*<<< orphan*/  reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct snd_kcontrol {int dummy; } ;
struct arizona {int /*<<< orphan*/ * mclk; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
#define  ARIZONA_CLK_SRC_MCLK1 131 
#define  ARIZONA_CLK_SRC_MCLK2 130 
 int ARIZONA_MCLK1 ; 
 int ARIZONA_MCLK2 ; 
 unsigned int ARIZONA_SYSCLK_SRC_MASK ; 
 unsigned int ARIZONA_SYSCLK_SRC_SHIFT ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

int arizona_clk_ev(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona *arizona = dev_get_drvdata(component->dev->parent);
	unsigned int val;
	int clk_idx;
	int ret;

	ret = regmap_read(arizona->regmap, w->reg, &val);
	if (ret) {
		dev_err(component->dev, "Failed to check clock source: %d\n", ret);
		return ret;
	}

	val = (val & ARIZONA_SYSCLK_SRC_MASK) >> ARIZONA_SYSCLK_SRC_SHIFT;

	switch (val) {
	case ARIZONA_CLK_SRC_MCLK1:
		clk_idx = ARIZONA_MCLK1;
		break;
	case ARIZONA_CLK_SRC_MCLK2:
		clk_idx = ARIZONA_MCLK2;
		break;
	default:
		return 0;
	}

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		return clk_prepare_enable(arizona->mclk[clk_idx]);
	case SND_SOC_DAPM_POST_PMD:
		clk_disable_unprepare(arizona->mclk[clk_idx]);
		return 0;
	default:
		return 0;
	}
}