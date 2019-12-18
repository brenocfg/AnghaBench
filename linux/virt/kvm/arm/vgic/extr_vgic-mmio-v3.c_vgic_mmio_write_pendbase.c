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
typedef  scalar_t__ u64 ;
struct vgic_cpu {int /*<<< orphan*/  pendbaser; scalar_t__ lpis_enabled; } ;
struct TYPE_2__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int gpa_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ cmpxchg64 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ update_64bit_reg (scalar_t__,int,unsigned int,unsigned long) ; 
 scalar_t__ vgic_sanitise_pendbaser (scalar_t__) ; 

__attribute__((used)) static void vgic_mmio_write_pendbase(struct kvm_vcpu *vcpu,
				     gpa_t addr, unsigned int len,
				     unsigned long val)
{
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	u64 old_pendbaser, pendbaser;

	/* Storing a value with LPIs already enabled is undefined */
	if (vgic_cpu->lpis_enabled)
		return;

	do {
		old_pendbaser = READ_ONCE(vgic_cpu->pendbaser);
		pendbaser = old_pendbaser;
		pendbaser = update_64bit_reg(pendbaser, addr & 4, len, val);
		pendbaser = vgic_sanitise_pendbaser(pendbaser);
	} while (cmpxchg64(&vgic_cpu->pendbaser, old_pendbaser,
			   pendbaser) != old_pendbaser);
}