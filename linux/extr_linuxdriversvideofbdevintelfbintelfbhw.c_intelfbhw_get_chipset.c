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
typedef  int u32 ;
struct pci_dev {int device; } ;
struct intelfb_info {char* name; int mobile; void* pll_index; int /*<<< orphan*/  chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_830M ; 
 int /*<<< orphan*/  INTEL_845G ; 
 int /*<<< orphan*/  INTEL_852GM ; 
 int /*<<< orphan*/  INTEL_852GME ; 
 int /*<<< orphan*/  INTEL_854 ; 
 int /*<<< orphan*/  INTEL_855GM ; 
 int /*<<< orphan*/  INTEL_855GME ; 
 int /*<<< orphan*/  INTEL_85XGM ; 
 int /*<<< orphan*/  INTEL_85X_CAPID ; 
 int INTEL_85X_VARIANT_MASK ; 
 int INTEL_85X_VARIANT_SHIFT ; 
 int /*<<< orphan*/  INTEL_865G ; 
 int /*<<< orphan*/  INTEL_915G ; 
 int /*<<< orphan*/  INTEL_915GM ; 
 int /*<<< orphan*/  INTEL_945G ; 
 int /*<<< orphan*/  INTEL_945GM ; 
 int /*<<< orphan*/  INTEL_945GME ; 
 int /*<<< orphan*/  INTEL_965G ; 
 int /*<<< orphan*/  INTEL_965GM ; 
#define  INTEL_VAR_852GM 143 
#define  INTEL_VAR_852GME 142 
#define  INTEL_VAR_855GM 141 
#define  INTEL_VAR_855GME 140 
#define  PCI_DEVICE_ID_INTEL_830M 139 
#define  PCI_DEVICE_ID_INTEL_845G 138 
#define  PCI_DEVICE_ID_INTEL_854 137 
#define  PCI_DEVICE_ID_INTEL_85XGM 136 
#define  PCI_DEVICE_ID_INTEL_865G 135 
#define  PCI_DEVICE_ID_INTEL_915G 134 
#define  PCI_DEVICE_ID_INTEL_915GM 133 
#define  PCI_DEVICE_ID_INTEL_945G 132 
#define  PCI_DEVICE_ID_INTEL_945GM 131 
#define  PCI_DEVICE_ID_INTEL_945GME 130 
#define  PCI_DEVICE_ID_INTEL_965G 129 
#define  PCI_DEVICE_ID_INTEL_965GM 128 
 void* PLLS_I8xx ; 
 void* PLLS_I9xx ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

int intelfbhw_get_chipset(struct pci_dev *pdev, struct intelfb_info *dinfo)
{
	u32 tmp;
	if (!pdev || !dinfo)
		return 1;

	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_830M:
		dinfo->name = "Intel(R) 830M";
		dinfo->chipset = INTEL_830M;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I8xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_845G:
		dinfo->name = "Intel(R) 845G";
		dinfo->chipset = INTEL_845G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I8xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_854:
		dinfo->mobile = 1;
		dinfo->name = "Intel(R) 854";
		dinfo->chipset = INTEL_854;
		return 0;
	case PCI_DEVICE_ID_INTEL_85XGM:
		tmp = 0;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I8xx;
		pci_read_config_dword(pdev, INTEL_85X_CAPID, &tmp);
		switch ((tmp >> INTEL_85X_VARIANT_SHIFT) &
			INTEL_85X_VARIANT_MASK) {
		case INTEL_VAR_855GME:
			dinfo->name = "Intel(R) 855GME";
			dinfo->chipset = INTEL_855GME;
			return 0;
		case INTEL_VAR_855GM:
			dinfo->name = "Intel(R) 855GM";
			dinfo->chipset = INTEL_855GM;
			return 0;
		case INTEL_VAR_852GME:
			dinfo->name = "Intel(R) 852GME";
			dinfo->chipset = INTEL_852GME;
			return 0;
		case INTEL_VAR_852GM:
			dinfo->name = "Intel(R) 852GM";
			dinfo->chipset = INTEL_852GM;
			return 0;
		default:
			dinfo->name = "Intel(R) 852GM/855GM";
			dinfo->chipset = INTEL_85XGM;
			return 0;
		}
		break;
	case PCI_DEVICE_ID_INTEL_865G:
		dinfo->name = "Intel(R) 865G";
		dinfo->chipset = INTEL_865G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I8xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_915G:
		dinfo->name = "Intel(R) 915G";
		dinfo->chipset = INTEL_915G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_915GM:
		dinfo->name = "Intel(R) 915GM";
		dinfo->chipset = INTEL_915GM;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_945G:
		dinfo->name = "Intel(R) 945G";
		dinfo->chipset = INTEL_945G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_945GM:
		dinfo->name = "Intel(R) 945GM";
		dinfo->chipset = INTEL_945GM;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_945GME:
		dinfo->name = "Intel(R) 945GME";
		dinfo->chipset = INTEL_945GME;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_965G:
		dinfo->name = "Intel(R) 965G";
		dinfo->chipset = INTEL_965G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	case PCI_DEVICE_ID_INTEL_965GM:
		dinfo->name = "Intel(R) 965GM";
		dinfo->chipset = INTEL_965GM;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		return 0;
	default:
		return 1;
	}
}