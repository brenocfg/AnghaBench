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
struct pci_dev {int subsystem_vendor; scalar_t__ subsystem_device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_SUBDEVICE_ID_QEMU ; 
 int PCI_SUBVENDOR_ID_REDHAT_QUMRANET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int inside_vm ; 

__attribute__((used)) static int snd_intel8x0_inside_vm(struct pci_dev *pci)
{
	int result  = inside_vm;
	char *msg   = NULL;

	/* check module parameter first (override detection) */
	if (result >= 0) {
		msg = result ? "enable (forced) VM" : "disable (forced) VM";
		goto fini;
	}

	/* check for known (emulated) devices */
	result = 0;
	if (pci->subsystem_vendor == PCI_SUBVENDOR_ID_REDHAT_QUMRANET &&
	    pci->subsystem_device == PCI_SUBDEVICE_ID_QEMU) {
		/* KVM emulated sound, PCI SSID: 1af4:1100 */
		msg = "enable KVM";
		result = 1;
	} else if (pci->subsystem_vendor == 0x1ab8) {
		/* Parallels VM emulated sound, PCI SSID: 1ab8:xxxx */
		msg = "enable Parallels VM";
		result = 1;
	}

fini:
	if (msg != NULL)
		dev_info(&pci->dev, "%s optimization\n", msg);

	return result;
}