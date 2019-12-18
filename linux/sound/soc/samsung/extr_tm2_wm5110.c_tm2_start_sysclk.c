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
struct tm2_machine_priv {int /*<<< orphan*/  sysclk_rate; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SRC_FLL1 ; 
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  ARIZONA_FLL_SRC_MCLK1 ; 
 int /*<<< orphan*/  MCLK_RATE ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM5110_FLL1 ; 
 int /*<<< orphan*/  WM5110_FLL1_REFCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tm2_machine_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tm2_start_sysclk(struct snd_soc_card *card)
{
	struct tm2_machine_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_component *component = priv->component;
	int ret;

	ret = snd_soc_component_set_pll(component, WM5110_FLL1_REFCLK,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    priv->sysclk_rate);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set FLL1 source: %d\n", ret);
		return ret;
	}

	ret = snd_soc_component_set_pll(component, WM5110_FLL1,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    priv->sysclk_rate);
	if (ret < 0) {
		dev_err(component->dev, "Failed to start FLL1: %d\n", ret);
		return ret;
	}

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_SYSCLK,
				       ARIZONA_CLK_SRC_FLL1,
				       priv->sysclk_rate,
				       SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set SYSCLK source: %d\n", ret);
		return ret;
	}

	return 0;
}