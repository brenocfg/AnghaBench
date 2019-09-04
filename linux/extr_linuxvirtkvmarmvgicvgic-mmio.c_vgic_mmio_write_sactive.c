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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGIC_ADDR_TO_INTID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __vgic_mmio_write_sactive (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_change_active_finish (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_change_active_prepare (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void vgic_mmio_write_sactive(struct kvm_vcpu *vcpu,
			     gpa_t addr, unsigned int len,
			     unsigned long val)
{
	u32 intid = VGIC_ADDR_TO_INTID(addr, 1);

	mutex_lock(&vcpu->kvm->lock);
	vgic_change_active_prepare(vcpu, intid);

	__vgic_mmio_write_sactive(vcpu, addr, len, val);

	vgic_change_active_finish(vcpu, intid);
	mutex_unlock(&vcpu->kvm->lock);
}