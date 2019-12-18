#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  mmio; int /*<<< orphan*/  irq; } ;
typedef  TYPE_1__ vortex_t ;
struct snd_device {TYPE_1__* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_core_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  vortex_gameport_unregister (TYPE_1__*) ; 

__attribute__((used)) static int snd_vortex_dev_free(struct snd_device *device)
{
	vortex_t *vortex = device->device_data;

	vortex_gameport_unregister(vortex);
	vortex_core_shutdown(vortex);
	// Take down PCI interface.
	free_irq(vortex->irq, vortex);
	iounmap(vortex->mmio);
	pci_release_regions(vortex->pci_dev);
	pci_disable_device(vortex->pci_dev);
	kfree(vortex);

	return 0;
}