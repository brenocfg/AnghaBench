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
struct skl {int /*<<< orphan*/ * nhlt; int /*<<< orphan*/  probe_work; TYPE_1__* skl_sst; int /*<<< orphan*/  pci; int /*<<< orphan*/  pci_id; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  device; } ;
struct hdac_bus {scalar_t__ mlcap; int /*<<< orphan*/  dev; scalar_t__ ppcap; } ;
struct TYPE_2__ {int /*<<< orphan*/  clock_power_gating; int /*<<< orphan*/  enable_miscbdcge; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_disable_async_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (int /*<<< orphan*/ ,struct hdac_bus*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int skl_clock_device_register (struct skl*) ; 
 int /*<<< orphan*/  skl_clock_device_unregister (struct skl*) ; 
 int /*<<< orphan*/  skl_clock_power_gating ; 
 int skl_create (struct pci_dev*,int /*<<< orphan*/ *,struct skl**) ; 
 int skl_dmic_device_register (struct skl*) ; 
 int /*<<< orphan*/  skl_enable_miscbdcge ; 
 int skl_find_machine (struct skl*,void*) ; 
 int skl_first_init (struct hdac_bus*) ; 
 int /*<<< orphan*/  skl_free (struct hdac_bus*) ; 
 int /*<<< orphan*/  skl_free_dsp (struct skl*) ; 
 int skl_init_dsp (struct skl*) ; 
 int skl_nhlt_create_sysfs (struct skl*) ; 
 int /*<<< orphan*/  skl_nhlt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skl_nhlt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_nhlt_update_topology_bin (struct skl*) ; 
 struct hdac_bus* skl_to_bus (struct skl*) ; 
 int /*<<< orphan*/  snd_hdac_bus_stop_chip (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_get_ml_capabilities (struct hdac_bus*) ; 

__attribute__((used)) static int skl_probe(struct pci_dev *pci,
		     const struct pci_device_id *pci_id)
{
	struct skl *skl;
	struct hdac_bus *bus = NULL;
	int err;

	/* we use ext core ops, so provide NULL for ops here */
	err = skl_create(pci, NULL, &skl);
	if (err < 0)
		return err;

	bus = skl_to_bus(skl);

	err = skl_first_init(bus);
	if (err < 0)
		goto out_free;

	skl->pci_id = pci->device;

	device_disable_async_suspend(bus->dev);

	skl->nhlt = skl_nhlt_init(bus->dev);

	if (skl->nhlt == NULL) {
		err = -ENODEV;
		goto out_free;
	}

	err = skl_nhlt_create_sysfs(skl);
	if (err < 0)
		goto out_nhlt_free;

	skl_nhlt_update_topology_bin(skl);

	pci_set_drvdata(skl->pci, bus);

	/* check if dsp is there */
	if (bus->ppcap) {
		/* create device for dsp clk */
		err = skl_clock_device_register(skl);
		if (err < 0)
			goto out_clk_free;

		err = skl_find_machine(skl, (void *)pci_id->driver_data);
		if (err < 0)
			goto out_nhlt_free;

		err = skl_init_dsp(skl);
		if (err < 0) {
			dev_dbg(bus->dev, "error failed to register dsp\n");
			goto out_nhlt_free;
		}
		skl->skl_sst->enable_miscbdcge = skl_enable_miscbdcge;
		skl->skl_sst->clock_power_gating = skl_clock_power_gating;
	}
	if (bus->mlcap)
		snd_hdac_ext_bus_get_ml_capabilities(bus);

	snd_hdac_bus_stop_chip(bus);

	/* create device for soc dmic */
	err = skl_dmic_device_register(skl);
	if (err < 0)
		goto out_dsp_free;

	schedule_work(&skl->probe_work);

	return 0;

out_dsp_free:
	skl_free_dsp(skl);
out_clk_free:
	skl_clock_device_unregister(skl);
out_nhlt_free:
	skl_nhlt_free(skl->nhlt);
out_free:
	skl_free(bus);

	return err;
}