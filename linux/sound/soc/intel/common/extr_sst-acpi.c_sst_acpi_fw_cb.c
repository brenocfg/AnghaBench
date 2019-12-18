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
struct sst_pdata {struct firmware const* fw; } ;
struct sst_acpi_priv {int /*<<< orphan*/  pdev_pcm; struct snd_soc_acpi_mach* mach; struct sst_acpi_desc* desc; struct sst_pdata sst_pdata; } ;
struct sst_acpi_desc {int /*<<< orphan*/  drv_name; } ;
struct snd_soc_acpi_mach {int /*<<< orphan*/  fw_filename; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,int /*<<< orphan*/ ,int,struct sst_pdata*,int) ; 
 struct sst_acpi_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void sst_acpi_fw_cb(const struct firmware *fw, void *context)
{
	struct platform_device *pdev = context;
	struct device *dev = &pdev->dev;
	struct sst_acpi_priv *sst_acpi = platform_get_drvdata(pdev);
	struct sst_pdata *sst_pdata = &sst_acpi->sst_pdata;
	struct sst_acpi_desc *desc = sst_acpi->desc;
	struct snd_soc_acpi_mach *mach = sst_acpi->mach;

	sst_pdata->fw = fw;
	if (!fw) {
		dev_err(dev, "Cannot load firmware %s\n", mach->fw_filename);
		return;
	}

	/* register PCM and DAI driver */
	sst_acpi->pdev_pcm =
		platform_device_register_data(dev, desc->drv_name, -1,
					      sst_pdata, sizeof(*sst_pdata));
	if (IS_ERR(sst_acpi->pdev_pcm)) {
		dev_err(dev, "Cannot register device %s. Error %d\n",
			desc->drv_name, (int)PTR_ERR(sst_acpi->pdev_pcm));
	}

	return;
}