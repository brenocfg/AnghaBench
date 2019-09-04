#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pendbaser; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int GICR_PENDBASER_PTZ ; 
 int /*<<< orphan*/  its_sync_lpi_pending_table (struct kvm_vcpu*) ; 

void vgic_enable_lpis(struct kvm_vcpu *vcpu)
{
	if (!(vcpu->arch.vgic_cpu.pendbaser & GICR_PENDBASER_PTZ))
		its_sync_lpi_pending_table(vcpu);
}