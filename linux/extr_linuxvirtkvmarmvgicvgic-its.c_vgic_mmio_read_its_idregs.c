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
struct vgic_its {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int GIC_PIDR2_ARCH_GICv3 ; 
#define  GITS_CIDR0 135 
#define  GITS_CIDR1 134 
#define  GITS_CIDR2 133 
#define  GITS_CIDR3 132 
#define  GITS_PIDR0 131 
#define  GITS_PIDR1 130 
#define  GITS_PIDR2 129 
#define  GITS_PIDR4 128 

__attribute__((used)) static unsigned long vgic_mmio_read_its_idregs(struct kvm *kvm,
					       struct vgic_its *its,
					       gpa_t addr, unsigned int len)
{
	switch (addr & 0xffff) {
	case GITS_PIDR0:
		return 0x92;	/* part number, bits[7:0] */
	case GITS_PIDR1:
		return 0xb4;	/* part number, bits[11:8] */
	case GITS_PIDR2:
		return GIC_PIDR2_ARCH_GICv3 | 0x0b;
	case GITS_PIDR4:
		return 0x40;	/* This is a 64K software visible page */
	/* The following are the ID registers for (any) GIC. */
	case GITS_CIDR0:
		return 0x0d;
	case GITS_CIDR1:
		return 0xf0;
	case GITS_CIDR2:
		return 0x05;
	case GITS_CIDR3:
		return 0xb1;
	}

	return 0;
}