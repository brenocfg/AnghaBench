#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vme_master_resource {unsigned int number; TYPE_1__* parent; } ;
struct ca91cx42_driver {scalar_t__ base; } ;
struct TYPE_2__ {struct ca91cx42_driver* driver_priv; } ;

/* Variables and functions */
 scalar_t__* CA91CX42_LSI_BD ; 
 scalar_t__* CA91CX42_LSI_BS ; 
 scalar_t__* CA91CX42_LSI_CTL ; 
 unsigned int CA91CX42_LSI_CTL_EN ; 
 unsigned int CA91CX42_LSI_CTL_PGM_PGM ; 
 unsigned int CA91CX42_LSI_CTL_SUPER_SUPR ; 
#define  CA91CX42_LSI_CTL_VAS_A16 137 
#define  CA91CX42_LSI_CTL_VAS_A24 136 
#define  CA91CX42_LSI_CTL_VAS_A32 135 
#define  CA91CX42_LSI_CTL_VAS_CRCSR 134 
 unsigned int CA91CX42_LSI_CTL_VAS_M ; 
#define  CA91CX42_LSI_CTL_VAS_USER1 133 
#define  CA91CX42_LSI_CTL_VAS_USER2 132 
 unsigned int CA91CX42_LSI_CTL_VCT_BLT ; 
#define  CA91CX42_LSI_CTL_VDW_D16 131 
#define  CA91CX42_LSI_CTL_VDW_D32 130 
#define  CA91CX42_LSI_CTL_VDW_D64 129 
#define  CA91CX42_LSI_CTL_VDW_D8 128 
 unsigned int CA91CX42_LSI_CTL_VDW_M ; 
 scalar_t__* CA91CX42_LSI_TO ; 
 scalar_t__ VME_A16 ; 
 scalar_t__ VME_A24 ; 
 scalar_t__ VME_A32 ; 
 scalar_t__ VME_BLT ; 
 scalar_t__ VME_CRCSR ; 
 scalar_t__ VME_D16 ; 
 scalar_t__ VME_D32 ; 
 scalar_t__ VME_D64 ; 
 scalar_t__ VME_D8 ; 
 scalar_t__ VME_DATA ; 
 scalar_t__ VME_PROG ; 
 scalar_t__ VME_SCT ; 
 scalar_t__ VME_SUPER ; 
 scalar_t__ VME_USER ; 
 scalar_t__ VME_USER1 ; 
 scalar_t__ VME_USER2 ; 
 void* ioread32 (scalar_t__) ; 

__attribute__((used)) static int __ca91cx42_master_get(struct vme_master_resource *image,
	int *enabled, unsigned long long *vme_base, unsigned long long *size,
	u32 *aspace, u32 *cycle, u32 *dwidth)
{
	unsigned int i, ctl;
	unsigned long long pci_base, pci_bound, vme_offset;
	struct ca91cx42_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	ctl = ioread32(bridge->base + CA91CX42_LSI_CTL[i]);

	pci_base = ioread32(bridge->base + CA91CX42_LSI_BS[i]);
	vme_offset = ioread32(bridge->base + CA91CX42_LSI_TO[i]);
	pci_bound = ioread32(bridge->base + CA91CX42_LSI_BD[i]);

	*vme_base = pci_base + vme_offset;
	*size = (unsigned long long)(pci_bound - pci_base);

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;
	*dwidth = 0;

	if (ctl & CA91CX42_LSI_CTL_EN)
		*enabled = 1;

	/* Setup address space */
	switch (ctl & CA91CX42_LSI_CTL_VAS_M) {
	case CA91CX42_LSI_CTL_VAS_A16:
		*aspace = VME_A16;
		break;
	case CA91CX42_LSI_CTL_VAS_A24:
		*aspace = VME_A24;
		break;
	case CA91CX42_LSI_CTL_VAS_A32:
		*aspace = VME_A32;
		break;
	case CA91CX42_LSI_CTL_VAS_CRCSR:
		*aspace = VME_CRCSR;
		break;
	case CA91CX42_LSI_CTL_VAS_USER1:
		*aspace = VME_USER1;
		break;
	case CA91CX42_LSI_CTL_VAS_USER2:
		*aspace = VME_USER2;
		break;
	}

	/* XXX Not sure howto check for MBLT */
	/* Setup cycle types */
	if (ctl & CA91CX42_LSI_CTL_VCT_BLT)
		*cycle |= VME_BLT;
	else
		*cycle |= VME_SCT;

	if (ctl & CA91CX42_LSI_CTL_SUPER_SUPR)
		*cycle |= VME_SUPER;
	else
		*cycle |= VME_USER;

	if (ctl & CA91CX42_LSI_CTL_PGM_PGM)
		*cycle = VME_PROG;
	else
		*cycle = VME_DATA;

	/* Setup data width */
	switch (ctl & CA91CX42_LSI_CTL_VDW_M) {
	case CA91CX42_LSI_CTL_VDW_D8:
		*dwidth = VME_D8;
		break;
	case CA91CX42_LSI_CTL_VDW_D16:
		*dwidth = VME_D16;
		break;
	case CA91CX42_LSI_CTL_VDW_D32:
		*dwidth = VME_D32;
		break;
	case CA91CX42_LSI_CTL_VDW_D64:
		*dwidth = VME_D64;
		break;
	}

	return 0;
}