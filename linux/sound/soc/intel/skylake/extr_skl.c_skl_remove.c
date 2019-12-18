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
struct skl_dev {int /*<<< orphan*/  nhlt; int /*<<< orphan*/  probe_work; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 struct skl_dev* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_nhlt_free (int /*<<< orphan*/ ) ; 
 struct hdac_bus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_clock_device_unregister (struct skl_dev*) ; 
 int /*<<< orphan*/  skl_dmic_device_unregister (struct skl_dev*) ; 
 int /*<<< orphan*/  skl_free (struct hdac_bus*) ; 
 int /*<<< orphan*/  skl_free_dsp (struct skl_dev*) ; 
 int /*<<< orphan*/  skl_machine_device_unregister (struct skl_dev*) ; 
 int /*<<< orphan*/  skl_nhlt_remove_sysfs (struct skl_dev*) ; 
 int /*<<< orphan*/  skl_platform_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_device_remove (struct hdac_bus*) ; 

__attribute__((used)) static void skl_remove(struct pci_dev *pci)
{
	struct hdac_bus *bus = pci_get_drvdata(pci);
	struct skl_dev *skl = bus_to_skl(bus);

	cancel_work_sync(&skl->probe_work);

	pm_runtime_get_noresume(&pci->dev);

	/* codec removal, invoke bus_device_remove */
	snd_hdac_ext_bus_device_remove(bus);

	skl_platform_unregister(&pci->dev);
	skl_free_dsp(skl);
	skl_machine_device_unregister(skl);
	skl_dmic_device_unregister(skl);
	skl_clock_device_unregister(skl);
	skl_nhlt_remove_sysfs(skl);
	intel_nhlt_free(skl->nhlt);
	skl_free(bus);
	dev_set_drvdata(&pci->dev, NULL);
}