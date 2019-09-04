#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_acpi_mach {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {struct snd_soc_acpi_mach* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;
struct cht_mc_private {int /*<<< orphan*/  mclk; int /*<<< orphan*/  codec_name; } ;
struct TYPE_13__ {int /*<<< orphan*/  codec_name; } ;
struct TYPE_11__ {TYPE_4__* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_9__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5672_I2C_DEFAULT ; 
 char* acpi_dev_get_first_match_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_9__* cht_dailink ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,char*) ; 
 struct cht_mc_private* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 TYPE_1__ snd_soc_card_cht ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct cht_mc_private*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cht_mc_probe(struct platform_device *pdev)
{
	int ret_val = 0;
	struct cht_mc_private *drv;
	struct snd_soc_acpi_mach *mach = pdev->dev.platform_data;
	const char *i2c_name;
	int i;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_ATOMIC);
	if (!drv)
		return -ENOMEM;

	strcpy(drv->codec_name, RT5672_I2C_DEFAULT);

	/* fixup codec name based on HID */
	if (mach) {
		i2c_name = acpi_dev_get_first_match_name(mach->id, NULL, -1);
		if (i2c_name) {
			snprintf(drv->codec_name, sizeof(drv->codec_name),
				 "i2c-%s", i2c_name);
			for (i = 0; i < ARRAY_SIZE(cht_dailink); i++) {
				if (!strcmp(cht_dailink[i].codec_name,
					    RT5672_I2C_DEFAULT)) {
					cht_dailink[i].codec_name =
						drv->codec_name;
					break;
				}
			}
		}
	}

	drv->mclk = devm_clk_get(&pdev->dev, "pmc_plt_clk_3");
	if (IS_ERR(drv->mclk)) {
		dev_err(&pdev->dev,
			"Failed to get MCLK from pmc_plt_clk_3: %ld\n",
			PTR_ERR(drv->mclk));
		return PTR_ERR(drv->mclk);
	}
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	/* register the soc card */
	snd_soc_card_cht.dev = &pdev->dev;
	ret_val = devm_snd_soc_register_card(&pdev->dev, &snd_soc_card_cht);
	if (ret_val) {
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		return ret_val;
	}
	platform_set_drvdata(pdev, &snd_soc_card_cht);
	return ret_val;
}