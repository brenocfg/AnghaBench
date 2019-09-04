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
struct tegra_asoc_utils_data {void* clk_pll_a; void* clk_pll_a_out0; void* clk_cdev1; struct device* dev; int /*<<< orphan*/  soc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  TEGRA_ASOC_UTILS_SOC_TEGRA114 ; 
 int /*<<< orphan*/  TEGRA_ASOC_UTILS_SOC_TEGRA124 ; 
 int /*<<< orphan*/  TEGRA_ASOC_UTILS_SOC_TEGRA20 ; 
 int /*<<< orphan*/  TEGRA_ASOC_UTILS_SOC_TEGRA30 ; 
 void* clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int tegra_asoc_utils_set_rate (struct tegra_asoc_utils_data*,int,int) ; 

int tegra_asoc_utils_init(struct tegra_asoc_utils_data *data,
			  struct device *dev)
{
	int ret;

	data->dev = dev;

	if (of_machine_is_compatible("nvidia,tegra20"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA20;
	else if (of_machine_is_compatible("nvidia,tegra30"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA30;
	else if (of_machine_is_compatible("nvidia,tegra114"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA114;
	else if (of_machine_is_compatible("nvidia,tegra124"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA124;
	else {
		dev_err(data->dev, "SoC unknown to Tegra ASoC utils\n");
		return -EINVAL;
	}

	data->clk_pll_a = clk_get(dev, "pll_a");
	if (IS_ERR(data->clk_pll_a)) {
		dev_err(data->dev, "Can't retrieve clk pll_a\n");
		ret = PTR_ERR(data->clk_pll_a);
		goto err;
	}

	data->clk_pll_a_out0 = clk_get(dev, "pll_a_out0");
	if (IS_ERR(data->clk_pll_a_out0)) {
		dev_err(data->dev, "Can't retrieve clk pll_a_out0\n");
		ret = PTR_ERR(data->clk_pll_a_out0);
		goto err_put_pll_a;
	}

	data->clk_cdev1 = clk_get(dev, "mclk");
	if (IS_ERR(data->clk_cdev1)) {
		dev_err(data->dev, "Can't retrieve clk cdev1\n");
		ret = PTR_ERR(data->clk_cdev1);
		goto err_put_pll_a_out0;
	}

	ret = tegra_asoc_utils_set_rate(data, 44100, 256 * 44100);
	if (ret)
		goto err_put_cdev1;

	return 0;

err_put_cdev1:
	clk_put(data->clk_cdev1);
err_put_pll_a_out0:
	clk_put(data->clk_pll_a_out0);
err_put_pll_a:
	clk_put(data->clk_pll_a);
err:
	return ret;
}