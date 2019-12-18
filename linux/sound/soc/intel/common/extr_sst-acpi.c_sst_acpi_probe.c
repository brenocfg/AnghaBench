#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sst_pdata {scalar_t__ resindex_dma_base; scalar_t__ dma_base; void* fw_size; int /*<<< orphan*/  fw_base; void* pcicfg_size; int /*<<< orphan*/  pcicfg_base; void* lpe_size; int /*<<< orphan*/  lpe_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  dma_engine; struct device* dma_dev; int /*<<< orphan*/  id; } ;
struct sst_acpi_priv {int /*<<< orphan*/  pdev_mach; struct snd_soc_acpi_mach* mach; struct sst_acpi_desc* desc; struct sst_pdata sst_pdata; } ;
struct sst_acpi_desc {scalar_t__ resindex_dma_base; scalar_t__ irqindex_host_ipc; scalar_t__ resindex_lpe_base; scalar_t__ resindex_pcicfg_base; scalar_t__ resindex_fw_base; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  dma_engine; int /*<<< orphan*/  sst_id; int /*<<< orphan*/  machines; } ;
struct snd_soc_acpi_mach {int /*<<< orphan*/  fw_filename; int /*<<< orphan*/  drv_name; struct sst_pdata* pdata; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {TYPE_1__* driver; } ;
struct platform_device {struct device dev; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sst_acpi_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,int /*<<< orphan*/ ,int,struct snd_soc_acpi_mach*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,scalar_t__) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sst_acpi_priv*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct platform_device*,int /*<<< orphan*/ ) ; 
 void* resource_size (struct resource*) ; 
 struct snd_soc_acpi_mach* snd_soc_acpi_find_machine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_acpi_fw_cb ; 

__attribute__((used)) static int sst_acpi_probe(struct platform_device *pdev)
{
	const struct acpi_device_id *id;
	struct device *dev = &pdev->dev;
	struct sst_acpi_priv *sst_acpi;
	struct sst_pdata *sst_pdata;
	struct snd_soc_acpi_mach *mach;
	struct sst_acpi_desc *desc;
	struct resource *mmio;
	int ret = 0;

	sst_acpi = devm_kzalloc(dev, sizeof(*sst_acpi), GFP_KERNEL);
	if (sst_acpi == NULL)
		return -ENOMEM;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!id)
		return -ENODEV;

	desc = (struct sst_acpi_desc *)id->driver_data;
	mach = snd_soc_acpi_find_machine(desc->machines);
	if (mach == NULL) {
		dev_err(dev, "No matching ASoC machine driver found\n");
		return -ENODEV;
	}

	sst_pdata = &sst_acpi->sst_pdata;
	sst_pdata->id = desc->sst_id;
	sst_pdata->dma_dev = dev;
	sst_acpi->desc = desc;
	sst_acpi->mach = mach;

	sst_pdata->resindex_dma_base = desc->resindex_dma_base;
	if (desc->resindex_dma_base >= 0) {
		sst_pdata->dma_engine = desc->dma_engine;
		sst_pdata->dma_base = desc->resindex_dma_base;
		sst_pdata->dma_size = desc->dma_size;
	}

	if (desc->irqindex_host_ipc >= 0)
		sst_pdata->irq = platform_get_irq(pdev, desc->irqindex_host_ipc);

	if (desc->resindex_lpe_base >= 0) {
		mmio = platform_get_resource(pdev, IORESOURCE_MEM,
					     desc->resindex_lpe_base);
		if (mmio) {
			sst_pdata->lpe_base = mmio->start;
			sst_pdata->lpe_size = resource_size(mmio);
		}
	}

	if (desc->resindex_pcicfg_base >= 0) {
		mmio = platform_get_resource(pdev, IORESOURCE_MEM,
					     desc->resindex_pcicfg_base);
		if (mmio) {
			sst_pdata->pcicfg_base = mmio->start;
			sst_pdata->pcicfg_size = resource_size(mmio);
		}
	}

	if (desc->resindex_fw_base >= 0) {
		mmio = platform_get_resource(pdev, IORESOURCE_MEM,
					     desc->resindex_fw_base);
		if (mmio) {
			sst_pdata->fw_base = mmio->start;
			sst_pdata->fw_size = resource_size(mmio);
		}
	}

	platform_set_drvdata(pdev, sst_acpi);
	mach->pdata = sst_pdata;

	/* register machine driver */
	sst_acpi->pdev_mach =
		platform_device_register_data(dev, mach->drv_name, -1,
					      mach, sizeof(*mach));
	if (IS_ERR(sst_acpi->pdev_mach))
		return PTR_ERR(sst_acpi->pdev_mach);

	/* continue SST probing after firmware is loaded */
	ret = request_firmware_nowait(THIS_MODULE, true, mach->fw_filename,
				      dev, GFP_KERNEL, pdev, sst_acpi_fw_cb);
	if (ret)
		platform_device_unregister(sst_acpi->pdev_mach);

	return ret;
}