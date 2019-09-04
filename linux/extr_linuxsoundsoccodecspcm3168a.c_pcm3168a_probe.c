#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct pcm3168a_priv {struct regmap* scki; TYPE_1__* supplies; struct regmap* regmap; int /*<<< orphan*/  sysclk; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct regmap*) ; 
 int /*<<< orphan*/  clk_get_rate (struct regmap*) ; 
 int clk_prepare_enable (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct pcm3168a_priv*) ; 
 struct regmap* devm_clk_get (struct device*,char*) ; 
 struct pcm3168a_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* pcm3168a_dais ; 
 int /*<<< orphan*/  pcm3168a_driver ; 
 int pcm3168a_reset (struct pcm3168a_priv*) ; 
 int /*<<< orphan*/ * pcm3168a_supply_names ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 

int pcm3168a_probe(struct device *dev, struct regmap *regmap)
{
	struct pcm3168a_priv *pcm3168a;
	int ret, i;

	pcm3168a = devm_kzalloc(dev, sizeof(*pcm3168a), GFP_KERNEL);
	if (pcm3168a == NULL)
		return -ENOMEM;

	dev_set_drvdata(dev, pcm3168a);

	pcm3168a->scki = devm_clk_get(dev, "scki");
	if (IS_ERR(pcm3168a->scki)) {
		ret = PTR_ERR(pcm3168a->scki);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire clock 'scki': %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(pcm3168a->scki);
	if (ret) {
		dev_err(dev, "Failed to enable mclk: %d\n", ret);
		return ret;
	}

	pcm3168a->sysclk = clk_get_rate(pcm3168a->scki);

	for (i = 0; i < ARRAY_SIZE(pcm3168a->supplies); i++)
		pcm3168a->supplies[i].supply = pcm3168a_supply_names[i];

	ret = devm_regulator_bulk_get(dev,
			ARRAY_SIZE(pcm3168a->supplies), pcm3168a->supplies);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request supplies: %d\n", ret);
		goto err_clk;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(pcm3168a->supplies),
				    pcm3168a->supplies);
	if (ret) {
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		goto err_clk;
	}

	pcm3168a->regmap = regmap;
	if (IS_ERR(pcm3168a->regmap)) {
		ret = PTR_ERR(pcm3168a->regmap);
		dev_err(dev, "failed to allocate regmap: %d\n", ret);
		goto err_regulator;
	}

	ret = pcm3168a_reset(pcm3168a);
	if (ret) {
		dev_err(dev, "Failed to reset device: %d\n", ret);
		goto err_regulator;
	}

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_idle(dev);

	ret = devm_snd_soc_register_component(dev, &pcm3168a_driver, pcm3168a_dais,
			ARRAY_SIZE(pcm3168a_dais));
	if (ret) {
		dev_err(dev, "failed to register component: %d\n", ret);
		goto err_regulator;
	}

	return 0;

err_regulator:
	regulator_bulk_disable(ARRAY_SIZE(pcm3168a->supplies),
			pcm3168a->supplies);
err_clk:
	clk_disable_unprepare(pcm3168a->scki);

	return ret;
}