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
struct vgic_redist_region {size_t count; } ;
struct kvm {int /*<<< orphan*/  online_vcpus; } ;

/* Variables and functions */
 size_t KVM_VGIC_V3_REDIST_SIZE ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline size_t
vgic_v3_rd_region_size(struct kvm *kvm, struct vgic_redist_region *rdreg)
{
	if (!rdreg->count)
		return atomic_read(&kvm->online_vcpus) * KVM_VGIC_V3_REDIST_SIZE;
	else
		return rdreg->count * KVM_VGIC_V3_REDIST_SIZE;
}