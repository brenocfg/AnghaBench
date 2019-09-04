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
struct sonicvibes {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  res_dmac; int /*<<< orphan*/  res_dmaa; int /*<<< orphan*/  dmac_port; int /*<<< orphan*/  dmaa_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct sonicvibes*) ; 
 int /*<<< orphan*/  kfree (struct sonicvibes*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sonicvibes_free_gameport (struct sonicvibes*) ; 

__attribute__((used)) static int snd_sonicvibes_free(struct sonicvibes *sonic)
{
	snd_sonicvibes_free_gameport(sonic);
	pci_write_config_dword(sonic->pci, 0x40, sonic->dmaa_port);
	pci_write_config_dword(sonic->pci, 0x48, sonic->dmac_port);
	if (sonic->irq >= 0)
		free_irq(sonic->irq, sonic);
	release_and_free_resource(sonic->res_dmaa);
	release_and_free_resource(sonic->res_dmac);
	pci_release_regions(sonic->pci);
	pci_disable_device(sonic->pci);
	kfree(sonic);
	return 0;
}