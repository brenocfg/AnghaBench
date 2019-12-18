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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_AMD_FE_GATE_7007 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_VIA_82C598_1 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_VIA_8365_1 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AMD ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_VIA ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_fix_agp_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  vortex_fix_latency (struct pci_dev*) ; 

__attribute__((used)) static void snd_vortex_workaround(struct pci_dev *vortex, int fix)
{
	struct pci_dev *via = NULL;

	/* autodetect if workarounds are required */
	if (fix == 255) {
		/* VIA KT133 */
		via = pci_get_device(PCI_VENDOR_ID_VIA,
			PCI_DEVICE_ID_VIA_8365_1, NULL);
		/* VIA Apollo */
		if (via == NULL) {
			via = pci_get_device(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_82C598_1, NULL);
			/* AMD Irongate */
			if (via == NULL)
				via = pci_get_device(PCI_VENDOR_ID_AMD,
					PCI_DEVICE_ID_AMD_FE_GATE_7007, NULL);
		}
		if (via) {
			dev_info(&vortex->dev,
				 "Activating latency workaround...\n");
			vortex_fix_latency(vortex);
			vortex_fix_agp_bridge(via);
		}
	} else {
		if (fix & 0x1)
			vortex_fix_latency(vortex);
		if ((fix & 0x2) && (via = pci_get_device(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_8365_1, NULL)))
			vortex_fix_agp_bridge(via);
		if ((fix & 0x4) && (via = pci_get_device(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_82C598_1, NULL)))
			vortex_fix_agp_bridge(via);
		if ((fix & 0x8) && (via = pci_get_device(PCI_VENDOR_ID_AMD,
				PCI_DEVICE_ID_AMD_FE_GATE_7007, NULL)))
			vortex_fix_agp_bridge(via);
	}
	pci_dev_put(via);
}