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
struct skl {int /*<<< orphan*/  probe_work; int /*<<< orphan*/  pci; scalar_t__ init_done; } ;
struct hdac_bus {scalar_t__ irq; scalar_t__ remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_SOC_HDAC_HDMI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct skl* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_bus_free_stream_pages (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_exit (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_ext_stop_streams (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_i915_exit (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_link_free_all (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_stream_free_all (struct hdac_bus*) ; 

__attribute__((used)) static int skl_free(struct hdac_bus *bus)
{
	struct skl *skl  = bus_to_skl(bus);

	skl->init_done = 0; /* to be sure */

	snd_hdac_ext_stop_streams(bus);

	if (bus->irq >= 0)
		free_irq(bus->irq, (void *)bus);
	snd_hdac_bus_free_stream_pages(bus);
	snd_hdac_stream_free_all(bus);
	snd_hdac_link_free_all(bus);

	if (bus->remap_addr)
		iounmap(bus->remap_addr);

	pci_release_regions(skl->pci);
	pci_disable_device(skl->pci);

	snd_hdac_ext_bus_exit(bus);

	cancel_work_sync(&skl->probe_work);
	if (IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI))
		snd_hdac_i915_exit(bus);

	return 0;
}