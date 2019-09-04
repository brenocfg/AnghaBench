#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tegra_utmip_config {int /*<<< orphan*/  xcvr_setup; int /*<<< orphan*/  xcvr_setup_use_fuses; int /*<<< orphan*/  hsdiscon_level; int /*<<< orphan*/  hssquelch_level; int /*<<< orphan*/  xcvr_hsslew; int /*<<< orphan*/  xcvr_lsrslew; int /*<<< orphan*/  xcvr_lsfslew; int /*<<< orphan*/  term_range_adj; int /*<<< orphan*/  idle_wait_delay; int /*<<< orphan*/  elastic_limit; int /*<<< orphan*/  hssync_start_delay; } ;
struct tegra_usb_phy {int is_ulpi_phy; TYPE_1__* soc_config; struct tegra_utmip_config* config; int /*<<< orphan*/  pad_regs; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {scalar_t__ requires_extra_tuning_parameters; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_utmip_config* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int read_utmi_param (struct platform_device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int utmi_phy_probe(struct tegra_usb_phy *tegra_phy,
			  struct platform_device *pdev)
{
	struct resource *res;
	int err;
	struct tegra_utmip_config *config;

	tegra_phy->is_ulpi_phy = false;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get UTMI pad regs\n");
		return  -ENXIO;
	}

	tegra_phy->pad_regs = devm_ioremap(&pdev->dev, res->start,
		resource_size(res));
	if (!tegra_phy->pad_regs) {
		dev_err(&pdev->dev, "Failed to remap UTMI pad regs\n");
		return -ENOMEM;
	}

	tegra_phy->config = devm_kzalloc(&pdev->dev, sizeof(*config),
					 GFP_KERNEL);
	if (!tegra_phy->config)
		return -ENOMEM;

	config = tegra_phy->config;

	err = read_utmi_param(pdev, "nvidia,hssync-start-delay",
		&config->hssync_start_delay);
	if (err < 0)
		return err;

	err = read_utmi_param(pdev, "nvidia,elastic-limit",
		&config->elastic_limit);
	if (err < 0)
		return err;

	err = read_utmi_param(pdev, "nvidia,idle-wait-delay",
		&config->idle_wait_delay);
	if (err < 0)
		return err;

	err = read_utmi_param(pdev, "nvidia,term-range-adj",
		&config->term_range_adj);
	if (err < 0)
		return err;

	err = read_utmi_param(pdev, "nvidia,xcvr-lsfslew",
		&config->xcvr_lsfslew);
	if (err < 0)
		return err;

	err = read_utmi_param(pdev, "nvidia,xcvr-lsrslew",
		&config->xcvr_lsrslew);
	if (err < 0)
		return err;

	if (tegra_phy->soc_config->requires_extra_tuning_parameters) {
		err = read_utmi_param(pdev, "nvidia,xcvr-hsslew",
			&config->xcvr_hsslew);
		if (err < 0)
			return err;

		err = read_utmi_param(pdev, "nvidia,hssquelch-level",
			&config->hssquelch_level);
		if (err < 0)
			return err;

		err = read_utmi_param(pdev, "nvidia,hsdiscon-level",
			&config->hsdiscon_level);
		if (err < 0)
			return err;
	}

	config->xcvr_setup_use_fuses = of_property_read_bool(
		pdev->dev.of_node, "nvidia,xcvr-setup-use-fuses");

	if (!config->xcvr_setup_use_fuses) {
		err = read_utmi_param(pdev, "nvidia,xcvr-setup",
			&config->xcvr_setup);
		if (err < 0)
			return err;
	}

	return 0;
}