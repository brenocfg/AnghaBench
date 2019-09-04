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
typedef  unsigned long u32 ;
struct vgic_its {unsigned long abi_rev; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 unsigned long GITS_IIDR_PRODUCTID_SHIFT ; 
 unsigned long GITS_IIDR_REV_MASK ; 
 unsigned long GITS_IIDR_REV_SHIFT ; 
 unsigned long IMPLEMENTER_ARM ; 
 unsigned long PRODUCT_ID_KVM ; 

__attribute__((used)) static unsigned long vgic_mmio_read_its_iidr(struct kvm *kvm,
					     struct vgic_its *its,
					     gpa_t addr, unsigned int len)
{
	u32 val;

	val = (its->abi_rev << GITS_IIDR_REV_SHIFT) & GITS_IIDR_REV_MASK;
	val |= (PRODUCT_ID_KVM << GITS_IIDR_PRODUCTID_SHIFT) | IMPLEMENTER_ARM;
	return val;
}