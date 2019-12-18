#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct sti_sas_dev_data {int /*<<< orphan*/  num_dapm_routes; int /*<<< orphan*/  dapm_routes; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  dac_ops; int /*<<< orphan*/  regmap; } ;
struct TYPE_14__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  virt_regmap; } ;
struct TYPE_13__ {int /*<<< orphan*/  regmap; } ;
struct sti_sas_data {struct sti_sas_dev_data* dev_data; TYPE_2__ dac; TYPE_1__ spdif; TYPE_5__* dev; } ;
struct TYPE_17__ {struct device_node* of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  ops; } ;
struct TYPE_15__ {int /*<<< orphan*/  num_dapm_routes; int /*<<< orphan*/  dapm_routes; int /*<<< orphan*/  num_dapm_widgets; int /*<<< orphan*/  dapm_widgets; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_4__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t STI_SAS_DAI_ANALOG_OUT ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_5__*,struct sti_sas_data*) ; 
 struct sti_sas_data* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init (TYPE_5__*,int /*<<< orphan*/ *,struct sti_sas_data*,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_5__*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 TYPE_4__* sti_sas_dai ; 
 int /*<<< orphan*/  sti_sas_dev_match ; 
 TYPE_3__ sti_sas_driver ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int sti_sas_driver_probe(struct platform_device *pdev)
{
	struct device_node *pnode = pdev->dev.of_node;
	struct sti_sas_data *drvdata;
	const struct of_device_id *of_id;

	/* Allocate device structure */
	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct sti_sas_data),
			       GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	/* Populate data structure depending on compatibility */
	of_id = of_match_node(sti_sas_dev_match, pnode);
	if (!of_id->data) {
		dev_err(&pdev->dev, "data associated to device is missing\n");
		return -EINVAL;
	}

	drvdata->dev_data = (struct sti_sas_dev_data *)of_id->data;

	/* Initialise device structure */
	drvdata->dev = &pdev->dev;

	/* Request the DAC & SPDIF registers memory region */
	drvdata->dac.virt_regmap = devm_regmap_init(&pdev->dev, NULL, drvdata,
						    drvdata->dev_data->regmap);
	if (IS_ERR(drvdata->dac.virt_regmap)) {
		dev_err(&pdev->dev, "audio registers not enabled\n");
		return PTR_ERR(drvdata->dac.virt_regmap);
	}

	/* Request the syscon region */
	drvdata->dac.regmap =
		syscon_regmap_lookup_by_phandle(pnode, "st,syscfg");
	if (IS_ERR(drvdata->dac.regmap)) {
		dev_err(&pdev->dev, "syscon registers not available\n");
		return PTR_ERR(drvdata->dac.regmap);
	}
	drvdata->spdif.regmap = drvdata->dac.regmap;

	sti_sas_dai[STI_SAS_DAI_ANALOG_OUT].ops = drvdata->dev_data->dac_ops;

	/* Set dapms*/
	sti_sas_driver.dapm_widgets = drvdata->dev_data->dapm_widgets;
	sti_sas_driver.num_dapm_widgets = drvdata->dev_data->num_dapm_widgets;

	sti_sas_driver.dapm_routes = drvdata->dev_data->dapm_routes;
	sti_sas_driver.num_dapm_routes = drvdata->dev_data->num_dapm_routes;

	/* Store context */
	dev_set_drvdata(&pdev->dev, drvdata);

	return devm_snd_soc_register_component(&pdev->dev, &sti_sas_driver,
					sti_sas_dai,
					ARRAY_SIZE(sti_sas_dai));
}