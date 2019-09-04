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
struct TYPE_4__ {int /*<<< orphan*/  its_vpe; } ;
struct TYPE_5__ {TYPE_1__ vgic_v3; } ;
struct TYPE_6__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int its_schedule_vpe (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vgic_supports_direct_msis (int /*<<< orphan*/ ) ; 

int vgic_v4_sync_hwstate(struct kvm_vcpu *vcpu)
{
	if (!vgic_supports_direct_msis(vcpu->kvm))
		return 0;

	return its_schedule_vpe(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe, false);
}