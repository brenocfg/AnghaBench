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
#define  GICD_PIDR2 128 

__attribute__((used)) static unsigned long vgic_mmio_read_v3_idregs(struct kvm_vcpu *vcpu,
					      gpa_t addr, unsigned int len)
{
	switch (addr & 0xffff) {
	case GICD_PIDR2:
		/* report a GICv3 compliant implementation */
		return 0x3b;
	}

	return 0;
}