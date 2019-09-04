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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5616_priv {struct snd_soc_component* component; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 struct rt5616_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5616_probe(struct snd_soc_component *component)
{
	struct rt5616_priv *rt5616 = snd_soc_component_get_drvdata(component);

	/* Check if MCLK provided */
	rt5616->mclk = devm_clk_get(component->dev, "mclk");
	if (PTR_ERR(rt5616->mclk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	rt5616->component = component;

	return 0;
}