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
struct kvm_vcpu {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int EINVAL ; 
#define  GICD_IIDR 128 
 unsigned long vgic_mmio_read_v3_misc (struct kvm_vcpu*,int,unsigned int) ; 
 int /*<<< orphan*/  vgic_mmio_write_v3_misc (struct kvm_vcpu*,int,unsigned int,unsigned long) ; 

__attribute__((used)) static int vgic_mmio_uaccess_write_v3_misc(struct kvm_vcpu *vcpu,
					   gpa_t addr, unsigned int len,
					   unsigned long val)
{
	switch (addr & 0x0c) {
	case GICD_IIDR:
		if (val != vgic_mmio_read_v3_misc(vcpu, addr, len))
			return -EINVAL;
	}

	vgic_mmio_write_v3_misc(vcpu, addr, len, val);
	return 0;
}