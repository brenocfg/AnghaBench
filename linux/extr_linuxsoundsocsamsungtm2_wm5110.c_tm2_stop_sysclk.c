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
struct tm2_machine_priv {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SRC_FLL1 ; 
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  WM5110_FLL1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tm2_machine_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tm2_stop_sysclk(struct snd_soc_card *card)
{
	struct tm2_machine_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_component *component = priv->component;
	int ret;

	ret = snd_soc_component_set_pll(component, WM5110_FLL1, 0, 0, 0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to stop FLL1: %d\n", ret);
		return ret;
	}

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_SYSCLK,
				       ARIZONA_CLK_SRC_FLL1, 0, 0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to stop SYSCLK: %d\n", ret);
		return ret;
	}

	return 0;
}