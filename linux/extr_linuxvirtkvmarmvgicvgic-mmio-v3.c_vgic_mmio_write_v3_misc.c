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
struct vgic_dist {int enabled; } ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
typedef  int gpa_t ;
struct TYPE_3__ {struct vgic_dist vgic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
#define  GICD_CTLR 130 
 unsigned long GICD_CTLR_ENABLE_SS_G1 ; 
#define  GICD_IIDR 129 
#define  GICD_TYPER 128 
 int /*<<< orphan*/  vgic_kick_vcpus (TYPE_2__*) ; 

__attribute__((used)) static void vgic_mmio_write_v3_misc(struct kvm_vcpu *vcpu,
				    gpa_t addr, unsigned int len,
				    unsigned long val)
{
	struct vgic_dist *dist = &vcpu->kvm->arch.vgic;
	bool was_enabled = dist->enabled;

	switch (addr & 0x0c) {
	case GICD_CTLR:
		dist->enabled = val & GICD_CTLR_ENABLE_SS_G1;

		if (!was_enabled && dist->enabled)
			vgic_kick_vcpus(vcpu->kvm);
		break;
	case GICD_TYPER:
	case GICD_IIDR:
		return;
	}
}