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
struct snd_soc_acpi_mach {int /*<<< orphan*/  fw_filename; } ;
struct skl_dev {int dummy; } ;
struct hdac_bus {scalar_t__ codec_mask; } ;

/* Variables and functions */
 struct hdac_bus* skl_to_bus (struct skl_dev*) ; 
 struct snd_soc_acpi_mach* snd_soc_acpi_intel_hda_machines ; 

__attribute__((used)) static struct snd_soc_acpi_mach *skl_find_hda_machine(struct skl_dev *skl,
					struct snd_soc_acpi_mach *machines)
{
	struct hdac_bus *bus = skl_to_bus(skl);
	struct snd_soc_acpi_mach *mach;

	/* check if we have any codecs detected on bus */
	if (bus->codec_mask == 0)
		return NULL;

	/* point to common table */
	mach = snd_soc_acpi_intel_hda_machines;

	/* all entries in the machine table use the same firmware */
	mach->fw_filename = machines->fw_filename;

	return mach;
}