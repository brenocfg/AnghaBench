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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,char*) ; 
 int pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quirk_io (struct pci_dev*,int,int,char*) ; 

__attribute__((used)) static void quirk_cs5536_vsa(struct pci_dev *dev)
{
	static char *name = "CS5536 ISA bridge";

	if (pci_resource_len(dev, 0) != 8) {
		quirk_io(dev, 0,   8, name);	/* SMB */
		quirk_io(dev, 1, 256, name);	/* GPIO */
		quirk_io(dev, 2,  64, name);	/* MFGPT */
		pci_info(dev, "%s bug detected (incorrect header); workaround applied\n",
			 name);
	}
}