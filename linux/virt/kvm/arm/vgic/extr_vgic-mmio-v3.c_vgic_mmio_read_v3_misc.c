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
typedef  int u32 ;
struct vgic_dist {int nr_spis; int implementation_rev; int /*<<< orphan*/  enabled; } ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
typedef  int gpa_t ;
struct TYPE_3__ {struct vgic_dist vgic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
#define  GICD_CTLR 130 
 int GICD_CTLR_ARE_NS ; 
 int GICD_CTLR_DS ; 
 int GICD_CTLR_ENABLE_SS_G1 ; 
#define  GICD_IIDR 129 
 int GICD_IIDR_IMPLEMENTER_SHIFT ; 
 int GICD_IIDR_PRODUCT_ID_SHIFT ; 
 int GICD_IIDR_REVISION_SHIFT ; 
#define  GICD_TYPER 128 
 int GICD_TYPER_LPIS ; 
 int IMPLEMENTER_ARM ; 
 int /*<<< orphan*/  INTERRUPT_ID_BITS_ITS ; 
 int /*<<< orphan*/  INTERRUPT_ID_BITS_SPIS ; 
 int PRODUCT_ID_KVM ; 
 int VGIC_NR_PRIVATE_IRQS ; 
 int /*<<< orphan*/  vgic_has_its (TYPE_2__*) ; 

__attribute__((used)) static unsigned long vgic_mmio_read_v3_misc(struct kvm_vcpu *vcpu,
					    gpa_t addr, unsigned int len)
{
	struct vgic_dist *vgic = &vcpu->kvm->arch.vgic;
	u32 value = 0;

	switch (addr & 0x0c) {
	case GICD_CTLR:
		if (vgic->enabled)
			value |= GICD_CTLR_ENABLE_SS_G1;
		value |= GICD_CTLR_ARE_NS | GICD_CTLR_DS;
		break;
	case GICD_TYPER:
		value = vgic->nr_spis + VGIC_NR_PRIVATE_IRQS;
		value = (value >> 5) - 1;
		if (vgic_has_its(vcpu->kvm)) {
			value |= (INTERRUPT_ID_BITS_ITS - 1) << 19;
			value |= GICD_TYPER_LPIS;
		} else {
			value |= (INTERRUPT_ID_BITS_SPIS - 1) << 19;
		}
		break;
	case GICD_IIDR:
		value = (PRODUCT_ID_KVM << GICD_IIDR_PRODUCT_ID_SHIFT) |
			(vgic->implementation_rev << GICD_IIDR_REVISION_SHIFT) |
			(IMPLEMENTER_ARM << GICD_IIDR_IMPLEMENTER_SHIFT);
		break;
	default:
		return 0;
	}

	return value;
}