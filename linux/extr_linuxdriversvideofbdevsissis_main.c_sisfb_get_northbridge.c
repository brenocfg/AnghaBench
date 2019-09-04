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
#define  PCI_DEVICE_ID_SI_540 139 
#define  PCI_DEVICE_ID_SI_550 138 
#define  PCI_DEVICE_ID_SI_630 137 
#define  PCI_DEVICE_ID_SI_650 136 
#define  PCI_DEVICE_ID_SI_651 135 
#define  PCI_DEVICE_ID_SI_660 134 
#define  PCI_DEVICE_ID_SI_661 133 
#define  PCI_DEVICE_ID_SI_730 132 
#define  PCI_DEVICE_ID_SI_740 131 
#define  PCI_DEVICE_ID_SI_741 130 
#define  PCI_DEVICE_ID_SI_760 129 
#define  PCI_DEVICE_ID_SI_761 128 
 int /*<<< orphan*/  PCI_VENDOR_ID_SI ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,unsigned short const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pci_dev *sisfb_get_northbridge(int basechipid)
{
	struct pci_dev *pdev = NULL;
	int nbridgenum, nbridgeidx, i;
	static const unsigned short nbridgeids[] = {
		PCI_DEVICE_ID_SI_540,	/* for SiS 540 VGA */
		PCI_DEVICE_ID_SI_630,	/* for SiS 630/730 VGA */
		PCI_DEVICE_ID_SI_730,
		PCI_DEVICE_ID_SI_550,   /* for SiS 550 VGA */
		PCI_DEVICE_ID_SI_650,   /* for SiS 650/651/740 VGA */
		PCI_DEVICE_ID_SI_651,
		PCI_DEVICE_ID_SI_740,
		PCI_DEVICE_ID_SI_661,	/* for SiS 661/741/660/760/761 VGA */
		PCI_DEVICE_ID_SI_741,
		PCI_DEVICE_ID_SI_660,
		PCI_DEVICE_ID_SI_760,
		PCI_DEVICE_ID_SI_761
	};

	switch(basechipid) {
#ifdef CONFIG_FB_SIS_300
	case SIS_540:	nbridgeidx = 0; nbridgenum = 1; break;
	case SIS_630:	nbridgeidx = 1; nbridgenum = 2; break;
#endif
#ifdef CONFIG_FB_SIS_315
	case SIS_550:   nbridgeidx = 3; nbridgenum = 1; break;
	case SIS_650:	nbridgeidx = 4; nbridgenum = 3; break;
	case SIS_660:	nbridgeidx = 7; nbridgenum = 5; break;
#endif
	default:	return NULL;
	}
	for(i = 0; i < nbridgenum; i++) {
		if((pdev = pci_get_device(PCI_VENDOR_ID_SI,
				nbridgeids[nbridgeidx+i], NULL)))
			break;
	}
	return pdev;
}