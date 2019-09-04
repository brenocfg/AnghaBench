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
struct TYPE_4__ {scalar_t__* vgic_lr; } ;
struct TYPE_5__ {TYPE_1__ vgic_v2; } ;
struct TYPE_6__ {TYPE_2__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */

void vgic_v2_clear_lr(struct kvm_vcpu *vcpu, int lr)
{
	vcpu->arch.vgic_cpu.vgic_v2.vgic_lr[lr] = 0;
}