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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_chip_hardrst (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_destroy_ha_caches (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_disable_ints (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_free_queues (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_remove_dev_attrs (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_turn_off_leds (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_unmap_ha (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_unregister_sas_ha (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct asd_ha_struct*) ; 
 int /*<<< orphan*/  kfree (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 struct asd_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ use_msi ; 

__attribute__((used)) static void asd_pci_remove(struct pci_dev *dev)
{
	struct asd_ha_struct *asd_ha = pci_get_drvdata(dev);

	if (!asd_ha)
		return;

	asd_unregister_sas_ha(asd_ha);

	asd_disable_ints(asd_ha);

	asd_remove_dev_attrs(asd_ha);

	/* XXX more here as needed */

	free_irq(dev->irq, asd_ha);
	if (use_msi)
		pci_disable_msi(asd_ha->pcidev);
	asd_turn_off_leds(asd_ha);
	asd_chip_hardrst(asd_ha);
	asd_free_queues(asd_ha);
	asd_destroy_ha_caches(asd_ha);
	asd_unmap_ha(asd_ha);
	kfree(asd_ha);
	pci_disable_device(dev);
	return;
}