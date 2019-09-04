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
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {scalar_t__ v2_groups_user_writable; } ;
struct TYPE_5__ {TYPE_1__ vgic; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  vgic_mmio_write_group (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

__attribute__((used)) static int vgic_mmio_uaccess_write_v2_group(struct kvm_vcpu *vcpu,
					    gpa_t addr, unsigned int len,
					    unsigned long val)
{
	if (vcpu->kvm->arch.vgic.v2_groups_user_writable)
		vgic_mmio_write_group(vcpu, addr, len, val);

	return 0;
}