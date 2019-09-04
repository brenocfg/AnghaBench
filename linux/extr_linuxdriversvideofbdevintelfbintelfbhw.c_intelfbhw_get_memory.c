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
typedef  int u16 ;
struct pci_dev {int device; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_MSG (char*,...) ; 
#define  INTEL_830_GMCH_GMS_DISABLED 149 
#define  INTEL_830_GMCH_GMS_LOCAL 148 
 int INTEL_830_GMCH_GMS_MASK ; 
#define  INTEL_830_GMCH_GMS_STOLEN_1024 147 
#define  INTEL_830_GMCH_GMS_STOLEN_512 146 
#define  INTEL_830_GMCH_GMS_STOLEN_8192 145 
#define  INTEL_855_GMCH_GMS_DISABLED 144 
 int INTEL_855_GMCH_GMS_MASK ; 
#define  INTEL_855_GMCH_GMS_STOLEN_16M 143 
#define  INTEL_855_GMCH_GMS_STOLEN_1M 142 
#define  INTEL_855_GMCH_GMS_STOLEN_32M 141 
#define  INTEL_855_GMCH_GMS_STOLEN_4M 140 
#define  INTEL_855_GMCH_GMS_STOLEN_8M 139 
#define  INTEL_915G_GMCH_GMS_STOLEN_48M 138 
#define  INTEL_915G_GMCH_GMS_STOLEN_64M 137 
 int /*<<< orphan*/  INTEL_GMCH_CTRL ; 
 int INTEL_GMCH_MEM_64M ; 
 int INTEL_GMCH_MEM_MASK ; 
 int KB (int) ; 
 int MB (int) ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PCI_DEVICE_ID_INTEL_830M 136 
#define  PCI_DEVICE_ID_INTEL_845G 135 
#define  PCI_DEVICE_ID_INTEL_915G 134 
#define  PCI_DEVICE_ID_INTEL_915GM 133 
#define  PCI_DEVICE_ID_INTEL_945G 132 
#define  PCI_DEVICE_ID_INTEL_945GM 131 
#define  PCI_DEVICE_ID_INTEL_945GME 130 
#define  PCI_DEVICE_ID_INTEL_965G 129 
#define  PCI_DEVICE_ID_INTEL_965GM 128 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_resource_start (struct pci_dev*,int) ; 

int intelfbhw_get_memory(struct pci_dev *pdev, int *aperture_size,
			 int *stolen_size)
{
	struct pci_dev *bridge_dev;
	u16 tmp;
	int stolen_overhead;

	if (!pdev || !aperture_size || !stolen_size)
		return 1;

	/* Find the bridge device.  It is always 0:0.0 */
	bridge_dev = pci_get_domain_bus_and_slot(pci_domain_nr(pdev->bus), 0,
						 PCI_DEVFN(0, 0));
	if (!bridge_dev) {
		ERR_MSG("cannot find bridge device\n");
		return 1;
	}

	/* Get the fb aperture size and "stolen" memory amount. */
	tmp = 0;
	pci_read_config_word(bridge_dev, INTEL_GMCH_CTRL, &tmp);
	pci_dev_put(bridge_dev);

	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_915G:
	case PCI_DEVICE_ID_INTEL_915GM:
	case PCI_DEVICE_ID_INTEL_945G:
	case PCI_DEVICE_ID_INTEL_945GM:
	case PCI_DEVICE_ID_INTEL_945GME:
	case PCI_DEVICE_ID_INTEL_965G:
	case PCI_DEVICE_ID_INTEL_965GM:
		/* 915, 945 and 965 chipsets support a 256MB aperture.
		   Aperture size is determined by inspected the
		   base address of the aperture. */
		if (pci_resource_start(pdev, 2) & 0x08000000)
			*aperture_size = MB(128);
		else
			*aperture_size = MB(256);
		break;
	default:
		if ((tmp & INTEL_GMCH_MEM_MASK) == INTEL_GMCH_MEM_64M)
			*aperture_size = MB(64);
		else
			*aperture_size = MB(128);
		break;
	}

	/* Stolen memory size is reduced by the GTT and the popup.
	   GTT is 1K per MB of aperture size, and popup is 4K. */
	stolen_overhead = (*aperture_size / MB(1)) + 4;
	switch(pdev->device) {
	case PCI_DEVICE_ID_INTEL_830M:
	case PCI_DEVICE_ID_INTEL_845G:
		switch (tmp & INTEL_830_GMCH_GMS_MASK) {
		case INTEL_830_GMCH_GMS_STOLEN_512:
			*stolen_size = KB(512) - KB(stolen_overhead);
			return 0;
		case INTEL_830_GMCH_GMS_STOLEN_1024:
			*stolen_size = MB(1) - KB(stolen_overhead);
			return 0;
		case INTEL_830_GMCH_GMS_STOLEN_8192:
			*stolen_size = MB(8) - KB(stolen_overhead);
			return 0;
		case INTEL_830_GMCH_GMS_LOCAL:
			ERR_MSG("only local memory found\n");
			return 1;
		case INTEL_830_GMCH_GMS_DISABLED:
			ERR_MSG("video memory is disabled\n");
			return 1;
		default:
			ERR_MSG("unexpected GMCH_GMS value: 0x%02x\n",
				tmp & INTEL_830_GMCH_GMS_MASK);
			return 1;
		}
		break;
	default:
		switch (tmp & INTEL_855_GMCH_GMS_MASK) {
		case INTEL_855_GMCH_GMS_STOLEN_1M:
			*stolen_size = MB(1) - KB(stolen_overhead);
			return 0;
		case INTEL_855_GMCH_GMS_STOLEN_4M:
			*stolen_size = MB(4) - KB(stolen_overhead);
			return 0;
		case INTEL_855_GMCH_GMS_STOLEN_8M:
			*stolen_size = MB(8) - KB(stolen_overhead);
			return 0;
		case INTEL_855_GMCH_GMS_STOLEN_16M:
			*stolen_size = MB(16) - KB(stolen_overhead);
			return 0;
		case INTEL_855_GMCH_GMS_STOLEN_32M:
			*stolen_size = MB(32) - KB(stolen_overhead);
			return 0;
		case INTEL_915G_GMCH_GMS_STOLEN_48M:
			*stolen_size = MB(48) - KB(stolen_overhead);
			return 0;
		case INTEL_915G_GMCH_GMS_STOLEN_64M:
			*stolen_size = MB(64) - KB(stolen_overhead);
			return 0;
		case INTEL_855_GMCH_GMS_DISABLED:
			ERR_MSG("video memory is disabled\n");
			return 0;
		default:
			ERR_MSG("unexpected GMCH_GMS value: 0x%02x\n",
				tmp & INTEL_855_GMCH_GMS_MASK);
			return 1;
		}
	}
}