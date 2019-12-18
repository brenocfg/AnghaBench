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
struct es8328_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct es8328_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int es8328_component_probe(struct snd_soc_component *component)
{
	struct es8328_priv *es8328;
	int ret;

	es8328 = snd_soc_component_get_drvdata(component);

	ret = regulator_bulk_enable(ARRAY_SIZE(es8328->supplies),
					es8328->supplies);
	if (ret) {
		dev_err(component->dev, "unable to enable regulators\n");
		return ret;
	}

	/* Setup clocks */
	es8328->clk = devm_clk_get(component->dev, NULL);
	if (IS_ERR(es8328->clk)) {
		dev_err(component->dev, "codec clock missing or invalid\n");
		ret = PTR_ERR(es8328->clk);
		goto clk_fail;
	}

	ret = clk_prepare_enable(es8328->clk);
	if (ret) {
		dev_err(component->dev, "unable to prepare codec clk\n");
		goto clk_fail;
	}

	return 0;

clk_fail:
	regulator_bulk_disable(ARRAY_SIZE(es8328->supplies),
			       es8328->supplies);
	return ret;
}