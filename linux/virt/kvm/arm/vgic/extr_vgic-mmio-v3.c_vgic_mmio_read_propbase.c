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
struct vgic_dist {int /*<<< orphan*/  propbaser; } ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
typedef  int gpa_t ;
struct TYPE_3__ {struct vgic_dist vgic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long extract_bytes (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static unsigned long vgic_mmio_read_propbase(struct kvm_vcpu *vcpu,
					     gpa_t addr, unsigned int len)
{
	struct vgic_dist *dist = &vcpu->kvm->arch.vgic;

	return extract_bytes(dist->propbaser, addr & 7, len);
}