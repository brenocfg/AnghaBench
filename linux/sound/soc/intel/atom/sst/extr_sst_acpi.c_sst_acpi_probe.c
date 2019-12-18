#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sst_platform_info {int platform; TYPE_3__* res_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  acpi_ipc_irq_index; } ;
struct snd_soc_acpi_mach {int drv_name; int /*<<< orphan*/  fw_filename; TYPE_2__ mach_params; struct sst_platform_info* pdata; } ;
struct device {TYPE_1__* driver; } ;
struct platform_device {struct device dev; } ;
struct intel_sst_drv {int /*<<< orphan*/  firmware_name; struct sst_platform_info* pdata; } ;
struct acpi_device_id {unsigned int id; scalar_t__ driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  acpi_ipc_irq_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct sst_platform_info byt_rvp_platform_data ; 
 TYPE_3__ bytcr_res_info ; 
 struct sst_platform_info chv_platform_data ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int kstrtouint (unsigned int,int,unsigned int*) ; 
 struct platform_device* platform_device_register_data (struct device*,int,int,void const*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct intel_sst_drv*) ; 
 struct snd_soc_acpi_mach* snd_soc_acpi_find_machine (struct snd_soc_acpi_mach*) ; 
 scalar_t__ soc_intel_is_byt () ; 
 scalar_t__ soc_intel_is_byt_cr (struct platform_device*) ; 
 int sst_alloc_drv_context (struct intel_sst_drv**,struct device*,unsigned int) ; 
 int /*<<< orphan*/  sst_configure_runtime_pm (struct intel_sst_drv*) ; 
 int sst_context_init (struct intel_sst_drv*) ; 
 int sst_platform_get_resources (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_acpi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret = 0;
	struct intel_sst_drv *ctx;
	const struct acpi_device_id *id;
	struct snd_soc_acpi_mach *mach;
	struct platform_device *mdev;
	struct platform_device *plat_dev;
	struct sst_platform_info *pdata;
	unsigned int dev_id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!id)
		return -ENODEV;
	dev_dbg(dev, "for %s\n", id->id);

	mach = (struct snd_soc_acpi_mach *)id->driver_data;
	mach = snd_soc_acpi_find_machine(mach);
	if (mach == NULL) {
		dev_err(dev, "No matching machine driver found\n");
		return -ENODEV;
	}

	if (soc_intel_is_byt())
		mach->pdata = &byt_rvp_platform_data;
	else
		mach->pdata = &chv_platform_data;
	pdata = mach->pdata;

	ret = kstrtouint(id->id, 16, &dev_id);
	if (ret < 0) {
		dev_err(dev, "Unique device id conversion error: %d\n", ret);
		return ret;
	}

	dev_dbg(dev, "ACPI device id: %x\n", dev_id);

	ret = sst_alloc_drv_context(&ctx, dev, dev_id);
	if (ret < 0)
		return ret;

	if (soc_intel_is_byt_cr(pdev)) {
		/* override resource info */
		byt_rvp_platform_data.res_info = &bytcr_res_info;
	}

	/* update machine parameters */
	mach->mach_params.acpi_ipc_irq_index =
		pdata->res_info->acpi_ipc_irq_index;

	plat_dev = platform_device_register_data(dev, pdata->platform, -1,
						NULL, 0);
	if (IS_ERR(plat_dev)) {
		dev_err(dev, "Failed to create machine device: %s\n",
			pdata->platform);
		return PTR_ERR(plat_dev);
	}

	/*
	 * Create platform device for sst machine driver,
	 * pass machine info as pdata
	 */
	mdev = platform_device_register_data(dev, mach->drv_name, -1,
					(const void *)mach, sizeof(*mach));
	if (IS_ERR(mdev)) {
		dev_err(dev, "Failed to create machine device: %s\n",
			mach->drv_name);
		return PTR_ERR(mdev);
	}

	/* Fill sst platform data */
	ctx->pdata = pdata;
	strcpy(ctx->firmware_name, mach->fw_filename);

	ret = sst_platform_get_resources(ctx);
	if (ret)
		return ret;

	ret = sst_context_init(ctx);
	if (ret < 0)
		return ret;

	sst_configure_runtime_pm(ctx);
	platform_set_drvdata(pdev, ctx);
	return ret;
}