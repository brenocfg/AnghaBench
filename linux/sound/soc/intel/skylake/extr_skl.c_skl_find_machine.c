#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dmic_num; } ;
struct snd_soc_acpi_mach {TYPE_1__ mach_params; struct skl_machine_pdata* pdata; int /*<<< orphan*/  fw_filename; } ;
struct skl_machine_pdata {int /*<<< orphan*/  use_tplg_pcm; } ;
struct skl_dev {int /*<<< orphan*/  nhlt; TYPE_2__* pci; int /*<<< orphan*/  use_tplg_pcm; int /*<<< orphan*/  fw_name; struct snd_soc_acpi_mach* mach; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intel_nhlt_get_dmic_geo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_soc_acpi_mach* skl_find_hda_machine (struct skl_dev*,void*) ; 
 struct hdac_bus* skl_to_bus (struct skl_dev*) ; 
 struct snd_soc_acpi_mach* snd_soc_acpi_find_machine (struct snd_soc_acpi_mach*) ; 

__attribute__((used)) static int skl_find_machine(struct skl_dev *skl, void *driver_data)
{
	struct hdac_bus *bus = skl_to_bus(skl);
	struct snd_soc_acpi_mach *mach = driver_data;
	struct skl_machine_pdata *pdata;

	mach = snd_soc_acpi_find_machine(mach);
	if (!mach) {
		dev_dbg(bus->dev, "No matching I2S machine driver found\n");
		mach = skl_find_hda_machine(skl, driver_data);
		if (!mach) {
			dev_err(bus->dev, "No matching machine driver found\n");
			return -ENODEV;
		}
	}

	skl->mach = mach;
	skl->fw_name = mach->fw_filename;
	pdata = mach->pdata;

	if (pdata) {
		skl->use_tplg_pcm = pdata->use_tplg_pcm;
		mach->mach_params.dmic_num =
			intel_nhlt_get_dmic_geo(&skl->pci->dev,
						skl->nhlt);
	}

	return 0;
}