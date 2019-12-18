#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* platform; } ;
struct snd_soc_acpi_mach {TYPE_1__ mach_params; } ;
struct device {struct snd_soc_acpi_mach* platform_data; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct dmi_system_id {scalar_t__ driver_data; } ;
struct cht_mc_private {unsigned long quirks; int /*<<< orphan*/  mclk; int /*<<< orphan*/  ts3a227e_present; } ;
struct TYPE_8__ {struct device* dev; scalar_t__ num_aux_devs; int /*<<< orphan*/ * aux_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int QUIRK_PMC_PLT_CLK_0 ; 
 int /*<<< orphan*/  acpi_dev_found (char*) ; 
 int /*<<< orphan*/  acpi_max98090_gpios ; 
 int /*<<< orphan*/  cht_max98090_quirk_table ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_acpi_dev_add_driver_gpios (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char const*) ; 
 struct cht_mc_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (struct device*,TYPE_2__*) ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 TYPE_2__ snd_soc_card_cht ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_2__*,struct cht_mc_private*) ; 
 int snd_soc_fixup_dai_links_platform_name (TYPE_2__*,char const*) ; 

__attribute__((used)) static int snd_cht_mc_probe(struct platform_device *pdev)
{
	const struct dmi_system_id *dmi_id;
	struct device *dev = &pdev->dev;
	int ret_val = 0;
	struct cht_mc_private *drv;
	const char *mclk_name;
	struct snd_soc_acpi_mach *mach;
	const char *platform_name;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	dmi_id = dmi_first_match(cht_max98090_quirk_table);
	if (dmi_id)
		drv->quirks = (unsigned long)dmi_id->driver_data;

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

	/* override plaform name, if required */
	snd_soc_card_cht.dev = &pdev->dev;
	mach = (&pdev->dev)->platform_data;
	platform_name = mach->mach_params.platform;

	ret_val = snd_soc_fixup_dai_links_platform_name(&snd_soc_card_cht,
							platform_name);
	if (ret_val)
		return ret_val;

	/* register the soc card */
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	if (drv->quirks & QUIRK_PMC_PLT_CLK_0)
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

	/*
	 * Boards which have the MAX98090's clk connected to clk_0 do not seem
	 * to like it if we muck with the clock. If we disable the clock when
	 * it is unused we get "max98090 i2c-193C9890:00: PLL unlocked" errors
	 * and the PLL never seems to lock again.
	 * So for these boards we enable it here once and leave it at that.
	 */
	if (drv->quirks & QUIRK_PMC_PLT_CLK_0) {
		ret_val = clk_prepare_enable(drv->mclk);
		if (ret_val < 0) {
			dev_err(&pdev->dev, "MCLK enable error: %d\n", ret_val);
			return ret_val;
		}
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