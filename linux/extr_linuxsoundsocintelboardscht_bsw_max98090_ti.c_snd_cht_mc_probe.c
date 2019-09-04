#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct dmi_system_id {scalar_t__ driver_data; } ;
struct cht_mc_private {int /*<<< orphan*/  mclk; int /*<<< orphan*/  ts3a227e_present; } ;
struct TYPE_5__ {struct device* dev; scalar_t__ num_aux_devs; int /*<<< orphan*/ * aux_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int QUIRK_PMC_PLT_CLK_0 ; 
 int /*<<< orphan*/  acpi_dev_found (char*) ; 
 int /*<<< orphan*/  acpi_max98090_gpios ; 
 int /*<<< orphan*/  cht_max98090_quirk_table ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_acpi_dev_add_driver_gpios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char const*) ; 
 struct cht_mc_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,TYPE_1__*) ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 TYPE_1__ snd_soc_card_cht ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct cht_mc_private*) ; 

__attribute__((used)) static int snd_cht_mc_probe(struct platform_device *pdev)
{
	const struct dmi_system_id *dmi_id;
	struct device *dev = &pdev->dev;
	int ret_val = 0;
	struct cht_mc_private *drv;
	const char *mclk_name;
	int quirks = 0;

	dmi_id = dmi_first_match(cht_max98090_quirk_table);
	if (dmi_id)
		quirks = (unsigned long)dmi_id->driver_data;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	drv->ts3a227e_present = acpi_dev_found("104C227E");
	if (!drv->ts3a227e_present) {
		/* no need probe TI jack detection chip */
		snd_soc_card_cht.aux_dev = NULL;
		snd_soc_card_cht.num_aux_devs = 0;

		ret_val = devm_acpi_dev_add_driver_gpios(dev->parent,
							 acpi_max98090_gpios);
		if (ret_val)
			dev_dbg(dev, "Unable to add GPIO mapping table\n");
	}

	/* register the soc card */
	snd_soc_card_cht.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	if (quirks & QUIRK_PMC_PLT_CLK_0)
		mclk_name = "pmc_plt_clk_0";
	else
		mclk_name = "pmc_plt_clk_3";

	drv->mclk = devm_clk_get(&pdev->dev, mclk_name);
	if (IS_ERR(drv->mclk)) {
		dev_err(&pdev->dev,
			"Failed to get MCLK from %s: %ld\n",
			mclk_name, PTR_ERR(drv->mclk));
		return PTR_ERR(drv->mclk);
	}

	ret_val = devm_snd_soc_register_card(&pdev->dev, &snd_soc_card_cht);
	if (ret_val) {
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		return ret_val;
	}
	platform_set_drvdata(pdev, &snd_soc_card_cht);
	return ret_val;
}