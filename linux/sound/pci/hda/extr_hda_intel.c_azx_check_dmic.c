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
struct pci_dev {int class; int /*<<< orphan*/  dev; } ;
struct nhlt_acpi_table {int dummy; } ;
struct azx {scalar_t__ driver_type; } ;

/* Variables and functions */
 scalar_t__ AZX_DRIVER_SKL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  intel_nhlt_free (struct nhlt_acpi_table*) ; 
 scalar_t__ intel_nhlt_get_dmic_geo (int /*<<< orphan*/ *,struct nhlt_acpi_table*) ; 
 struct nhlt_acpi_table* intel_nhlt_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int azx_check_dmic(struct pci_dev *pci, struct azx *chip)
{
	struct nhlt_acpi_table *nhlt;
	int ret = 0;

	if (chip->driver_type == AZX_DRIVER_SKL &&
	    pci->class != 0x040300) {
		nhlt = intel_nhlt_init(&pci->dev);
		if (nhlt) {
			if (intel_nhlt_get_dmic_geo(&pci->dev, nhlt)) {
				ret = -ENODEV;
				dev_info(&pci->dev, "Digital mics found on Skylake+ platform, aborting probe\n");
			}
			intel_nhlt_free(nhlt);
		}
	}
	return ret;
}