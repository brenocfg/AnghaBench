#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_pcie {int num_supplies; TYPE_1__* supplies; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_4__ {char* supply; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,TYPE_1__*) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_regulator_bulk_available (struct device_node*,TYPE_1__*,int) ; 
 int tegra_pcie_get_legacy_regulators (struct tegra_pcie*) ; 

__attribute__((used)) static int tegra_pcie_get_regulators(struct tegra_pcie *pcie, u32 lane_mask)
{
	struct device *dev = pcie->dev;
	struct device_node *np = dev->of_node;
	unsigned int i = 0;

	if (of_device_is_compatible(np, "nvidia,tegra186-pcie")) {
		pcie->num_supplies = 4;

		pcie->supplies = devm_kcalloc(pcie->dev, pcie->num_supplies,
					      sizeof(*pcie->supplies),
					      GFP_KERNEL);
		if (!pcie->supplies)
			return -ENOMEM;

		pcie->supplies[i++].supply = "dvdd-pex";
		pcie->supplies[i++].supply = "hvdd-pex-pll";
		pcie->supplies[i++].supply = "hvdd-pex";
		pcie->supplies[i++].supply = "vddio-pexctl-aud";
	} else if (of_device_is_compatible(np, "nvidia,tegra210-pcie")) {
		pcie->num_supplies = 6;

		pcie->supplies = devm_kcalloc(pcie->dev, pcie->num_supplies,
					      sizeof(*pcie->supplies),
					      GFP_KERNEL);
		if (!pcie->supplies)
			return -ENOMEM;

		pcie->supplies[i++].supply = "avdd-pll-uerefe";
		pcie->supplies[i++].supply = "hvddio-pex";
		pcie->supplies[i++].supply = "dvddio-pex";
		pcie->supplies[i++].supply = "dvdd-pex-pll";
		pcie->supplies[i++].supply = "hvdd-pex-pll-e";
		pcie->supplies[i++].supply = "vddio-pex-ctl";
	} else if (of_device_is_compatible(np, "nvidia,tegra124-pcie")) {
		pcie->num_supplies = 7;

		pcie->supplies = devm_kcalloc(dev, pcie->num_supplies,
					      sizeof(*pcie->supplies),
					      GFP_KERNEL);
		if (!pcie->supplies)
			return -ENOMEM;

		pcie->supplies[i++].supply = "avddio-pex";
		pcie->supplies[i++].supply = "dvddio-pex";
		pcie->supplies[i++].supply = "avdd-pex-pll";
		pcie->supplies[i++].supply = "hvdd-pex";
		pcie->supplies[i++].supply = "hvdd-pex-pll-e";
		pcie->supplies[i++].supply = "vddio-pex-ctl";
		pcie->supplies[i++].supply = "avdd-pll-erefe";
	} else if (of_device_is_compatible(np, "nvidia,tegra30-pcie")) {
		bool need_pexa = false, need_pexb = false;

		/* VDD_PEXA and AVDD_PEXA supply lanes 0 to 3 */
		if (lane_mask & 0x0f)
			need_pexa = true;

		/* VDD_PEXB and AVDD_PEXB supply lanes 4 to 5 */
		if (lane_mask & 0x30)
			need_pexb = true;

		pcie->num_supplies = 4 + (need_pexa ? 2 : 0) +
					 (need_pexb ? 2 : 0);

		pcie->supplies = devm_kcalloc(dev, pcie->num_supplies,
					      sizeof(*pcie->supplies),
					      GFP_KERNEL);
		if (!pcie->supplies)
			return -ENOMEM;

		pcie->supplies[i++].supply = "avdd-pex-pll";
		pcie->supplies[i++].supply = "hvdd-pex";
		pcie->supplies[i++].supply = "vddio-pex-ctl";
		pcie->supplies[i++].supply = "avdd-plle";

		if (need_pexa) {
			pcie->supplies[i++].supply = "avdd-pexa";
			pcie->supplies[i++].supply = "vdd-pexa";
		}

		if (need_pexb) {
			pcie->supplies[i++].supply = "avdd-pexb";
			pcie->supplies[i++].supply = "vdd-pexb";
		}
	} else if (of_device_is_compatible(np, "nvidia,tegra20-pcie")) {
		pcie->num_supplies = 5;

		pcie->supplies = devm_kcalloc(dev, pcie->num_supplies,
					      sizeof(*pcie->supplies),
					      GFP_KERNEL);
		if (!pcie->supplies)
			return -ENOMEM;

		pcie->supplies[0].supply = "avdd-pex";
		pcie->supplies[1].supply = "vdd-pex";
		pcie->supplies[2].supply = "avdd-pex-pll";
		pcie->supplies[3].supply = "avdd-plle";
		pcie->supplies[4].supply = "vddio-pex-clk";
	}

	if (of_regulator_bulk_available(dev->of_node, pcie->supplies,
					pcie->num_supplies))
		return devm_regulator_bulk_get(dev, pcie->num_supplies,
					       pcie->supplies);

	/*
	 * If not all regulators are available for this new scheme, assume
	 * that the device tree complies with an older version of the device
	 * tree binding.
	 */
	dev_info(dev, "using legacy DT binding for power supplies\n");

	devm_kfree(dev, pcie->supplies);
	pcie->num_supplies = 0;

	return tegra_pcie_get_legacy_regulators(pcie);
}