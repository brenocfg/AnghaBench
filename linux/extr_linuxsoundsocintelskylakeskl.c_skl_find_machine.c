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
struct snd_soc_acpi_mach {struct skl_machine_pdata* pdata; int /*<<< orphan*/  fw_filename; } ;
struct skl_machine_pdata {int /*<<< orphan*/  dmic_num; int /*<<< orphan*/  use_tplg_pcm; } ;
struct skl {int /*<<< orphan*/  use_tplg_pcm; int /*<<< orphan*/  fw_name; struct snd_soc_acpi_mach* mach; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skl_get_dmic_geo (struct skl*) ; 
 struct hdac_bus* skl_to_bus (struct skl*) ; 
 struct snd_soc_acpi_mach* snd_soc_acpi_find_machine (struct snd_soc_acpi_mach*) ; 

__attribute__((used)) static int skl_find_machine(struct skl *skl, void *driver_data)
{
	struct hdac_bus *bus = skl_to_bus(skl);
	struct snd_soc_acpi_mach *mach = driver_data;
	struct skl_machine_pdata *pdata;

	mach = snd_soc_acpi_find_machine(mach);
	if (mach == NULL) {
		dev_err(bus->dev, "No matching machine driver found\n");
		return -ENODEV;
	}

	skl->mach = mach;
	skl->fw_name = mach->fw_filename;
	pdata = mach->pdata;

	if (pdata) {
		skl->use_tplg_pcm = pdata->use_tplg_pcm;
		pdata->dmic_num = skl_get_dmic_geo(skl);
	}

	return 0;
}