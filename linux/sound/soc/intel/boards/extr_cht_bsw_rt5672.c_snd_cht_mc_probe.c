#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {char* platform; } ;
struct snd_soc_acpi_mach {TYPE_2__ mach_params; int /*<<< orphan*/  id; } ;
struct TYPE_18__ {struct snd_soc_acpi_mach* platform_data; } ;
struct platform_device {TYPE_7__ dev; } ;
struct cht_mc_private {int /*<<< orphan*/  mclk; int /*<<< orphan*/  codec_name; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {TYPE_7__* dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {TYPE_1__* codecs; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_12__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5672_I2C_DEFAULT ; 
 struct acpi_device* acpi_dev_get_first_match_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* acpi_dev_name (struct acpi_device*) ; 
 TYPE_12__* cht_dailink ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_7__*,char*) ; 
 struct cht_mc_private* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_7__*,TYPE_3__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 TYPE_3__ snd_soc_card_cht ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_3__*,struct cht_mc_private*) ; 
 int snd_soc_fixup_dai_links_platform_name (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cht_mc_probe(struct platform_device *pdev)
{
	int ret_val = 0;
	struct cht_mc_private *drv;
	struct snd_soc_acpi_mach *mach = pdev->dev.platform_data;
	const char *platform_name;
	struct acpi_device *adev;
	int i;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	strcpy(drv->codec_name, RT5672_I2C_DEFAULT);

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, NULL, -1);
	if (adev) {
		snprintf(drv->codec_name, sizeof(drv->codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		put_device(&adev->dev);
		for (i = 0; i < ARRAY_SIZE(cht_dailink); i++) {
			if (!strcmp(cht_dailink[i].codecs->name,
				    RT5672_I2C_DEFAULT)) {
				cht_dailink[i].codecs->name = drv->codec_name;
				break;
			}
		}
	}

	/* override plaform name, if required */
	snd_soc_card_cht.dev = &pdev->dev;
	platform_name = mach->mach_params.platform;

	ret_val = snd_soc_fixup_dai_links_platform_name(&snd_soc_card_cht,
							platform_name);
	if (ret_val)
		return ret_val;

	drv->mclk = devm_clk_get(&pdev->dev, "pmc_plt_clk_3");
	if (IS_ERR(drv->mclk)) {
		dev_err(&pdev->dev,
			"Failed to get MCLK from pmc_plt_clk_3: %ld\n",
			PTR_ERR(drv->mclk));
		return PTR_ERR(drv->mclk);
	}
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	/* register the soc card */
	ret_val = devm_snd_soc_register_card(&pdev->dev, &snd_soc_card_cht);
	if (ret_val) {
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		return ret_val;
	}
	platform_set_drvdata(pdev, &snd_soc_card_cht);
	return ret_val;
}