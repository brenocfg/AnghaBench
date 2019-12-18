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
struct twl6040_data {int /*<<< orphan*/  sysclk; int /*<<< orphan*/  clk_in; int /*<<< orphan*/  pll; } ;
struct twl6040 {int dummy; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct twl6040* to_twl6040 (struct snd_soc_component*) ; 
 int twl6040_set_pll (struct twl6040*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6040_prepare(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct twl6040 *twl6040 = to_twl6040(component);
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);
	int ret;

	if (!priv->sysclk) {
		dev_err(component->dev,
			"no mclk configured, call set_sysclk() on init\n");
		return -EINVAL;
	}

	ret = twl6040_set_pll(twl6040, priv->pll, priv->clk_in, priv->sysclk);
	if (ret) {
		dev_err(component->dev, "Can not set PLL (%d)\n", ret);
		return -EPERM;
	}

	return 0;
}