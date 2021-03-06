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
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  __vgic_mmio_write_cactive (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

int vgic_mmio_uaccess_write_cactive(struct kvm_vcpu *vcpu,
				     gpa_t addr, unsigned int len,
				     unsigned long val)
{
	__vgic_mmio_write_cactive(vcpu, addr, len, val);
	return 0;
}