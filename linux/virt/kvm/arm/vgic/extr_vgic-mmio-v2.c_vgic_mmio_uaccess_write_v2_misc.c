#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_3__* kvm; } ;
typedef  int gpa_t ;
struct TYPE_4__ {int v2_groups_user_writable; } ;
struct TYPE_5__ {TYPE_1__ vgic; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GIC_DIST_IIDR 128 
 unsigned long vgic_mmio_read_v2_misc (struct kvm_vcpu*,int,unsigned int) ; 
 int /*<<< orphan*/  vgic_mmio_write_v2_misc (struct kvm_vcpu*,int,unsigned int,unsigned long) ; 

__attribute__((used)) static int vgic_mmio_uaccess_write_v2_misc(struct kvm_vcpu *vcpu,
					   gpa_t addr, unsigned int len,
					   unsigned long val)
{
	switch (addr & 0x0c) {
	case GIC_DIST_IIDR:
		if (val != vgic_mmio_read_v2_misc(vcpu, addr, len))
			return -EINVAL;

		/*
		 * If we observe a write to GICD_IIDR we know that userspace
		 * has been updated and has had a chance to cope with older
		 * kernels (VGICv2 IIDR.Revision == 0) incorrectly reporting
		 * interrupts as group 1, and therefore we now allow groups to
		 * be user writable.  Doing this by default would break
		 * migration from old kernels to new kernels with legacy
		 * userspace.
		 */
		vcpu->kvm->arch.vgic.v2_groups_user_writable = true;
		return 0;
	}

	vgic_mmio_write_v2_misc(vcpu, addr, len, val);
	return 0;
}