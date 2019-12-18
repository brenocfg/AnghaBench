#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct pcm512x_priv {int pll_in; int pll_out; TYPE_1__* supplies; int /*<<< orphan*/  sclk; struct regmap* regmap; TYPE_3__* supply_nb; int /*<<< orphan*/  mutex; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_6__ {int /*<<< orphan*/  consumer; int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM512x_POWER ; 
 int /*<<< orphan*/  PCM512x_RESET ; 
 int /*<<< orphan*/  PCM512x_RQST ; 
 int PCM512x_RSTM ; 
 int PCM512x_RSTR ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct pcm512x_priv*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct pcm512x_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int devm_regulator_register_notifier (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (struct device_node const*,char*,int*) ; 
 int /*<<< orphan*/  pcm512x_component_driver ; 
 int /*<<< orphan*/  pcm512x_dai ; 
 int /*<<< orphan*/  pcm512x_regulator_event_0 ; 
 int /*<<< orphan*/  pcm512x_regulator_event_1 ; 
 int /*<<< orphan*/  pcm512x_regulator_event_2 ; 
 int /*<<< orphan*/ * pcm512x_supply_names ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 

int pcm512x_probe(struct device *dev, struct regmap *regmap)
{
	struct pcm512x_priv *pcm512x;
	int i, ret;

	pcm512x = devm_kzalloc(dev, sizeof(struct pcm512x_priv), GFP_KERNEL);
	if (!pcm512x)
		return -ENOMEM;

	mutex_init(&pcm512x->mutex);

	dev_set_drvdata(dev, pcm512x);
	pcm512x->regmap = regmap;

	for (i = 0; i < ARRAY_SIZE(pcm512x->supplies); i++)
		pcm512x->supplies[i].supply = pcm512x_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(pcm512x->supplies),
				      pcm512x->supplies);
	if (ret != 0) {
		dev_err(dev, "Failed to get supplies: %d\n", ret);
		return ret;
	}

	pcm512x->supply_nb[0].notifier_call = pcm512x_regulator_event_0;
	pcm512x->supply_nb[1].notifier_call = pcm512x_regulator_event_1;
	pcm512x->supply_nb[2].notifier_call = pcm512x_regulator_event_2;

	for (i = 0; i < ARRAY_SIZE(pcm512x->supplies); i++) {
		ret = devm_regulator_register_notifier(
						pcm512x->supplies[i].consumer,
						&pcm512x->supply_nb[i]);
		if (ret != 0) {
			dev_err(dev,
				"Failed to register regulator notifier: %d\n",
				ret);
		}
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(pcm512x->supplies),
				    pcm512x->supplies);
	if (ret != 0) {
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	/* Reset the device, verifying I/O in the process for I2C */
	ret = regmap_write(regmap, PCM512x_RESET,
			   PCM512x_RSTM | PCM512x_RSTR);
	if (ret != 0) {
		dev_err(dev, "Failed to reset device: %d\n", ret);
		goto err;
	}

	ret = regmap_write(regmap, PCM512x_RESET, 0);
	if (ret != 0) {
		dev_err(dev, "Failed to reset device: %d\n", ret);
		goto err;
	}

	pcm512x->sclk = devm_clk_get(dev, NULL);
	if (PTR_ERR(pcm512x->sclk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (!IS_ERR(pcm512x->sclk)) {
		ret = clk_prepare_enable(pcm512x->sclk);
		if (ret != 0) {
			dev_err(dev, "Failed to enable SCLK: %d\n", ret);
			return ret;
		}
	}

	/* Default to standby mode */
	ret = regmap_update_bits(pcm512x->regmap, PCM512x_POWER,
				 PCM512x_RQST, PCM512x_RQST);
	if (ret != 0) {
		dev_err(dev, "Failed to request standby: %d\n",
			ret);
		goto err_clk;
	}

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_idle(dev);

#ifdef CONFIG_OF
	if (dev->of_node) {
		const struct device_node *np = dev->of_node;
		u32 val;

		if (of_property_read_u32(np, "pll-in", &val) >= 0) {
			if (val > 6) {
				dev_err(dev, "Invalid pll-in\n");
				ret = -EINVAL;
				goto err_clk;
			}
			pcm512x->pll_in = val;
		}

		if (of_property_read_u32(np, "pll-out", &val) >= 0) {
			if (val > 6) {
				dev_err(dev, "Invalid pll-out\n");
				ret = -EINVAL;
				goto err_clk;
			}
			pcm512x->pll_out = val;
		}

		if (!pcm512x->pll_in != !pcm512x->pll_out) {
			dev_err(dev,
				"Error: both pll-in and pll-out, or none\n");
			ret = -EINVAL;
			goto err_clk;
		}
		if (pcm512x->pll_in && pcm512x->pll_in == pcm512x->pll_out) {
			dev_err(dev, "Error: pll-in == pll-out\n");
			ret = -EINVAL;
			goto err_clk;
		}
	}
#endif

	ret = devm_snd_soc_register_component(dev, &pcm512x_component_driver,
				    &pcm512x_dai, 1);
	if (ret != 0) {
		dev_err(dev, "Failed to register CODEC: %d\n", ret);
		goto err_pm;
	}

	return 0;

err_pm:
	pm_runtime_disable(dev);
err_clk:
	if (!IS_ERR(pcm512x->sclk))
		clk_disable_unprepare(pcm512x->sclk);
err:
	regulator_bulk_disable(ARRAY_SIZE(pcm512x->supplies),
				     pcm512x->supplies);
	return ret;
}