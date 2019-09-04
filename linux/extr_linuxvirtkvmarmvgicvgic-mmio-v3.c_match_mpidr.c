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
typedef  unsigned long u64 ;
typedef  int u16 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MPIDR_AFFINITY_LEVEL (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long MPIDR_LEVEL_MASK ; 
 unsigned long kvm_vcpu_get_mpidr_aff (struct kvm_vcpu*) ; 

__attribute__((used)) static int match_mpidr(u64 sgi_aff, u16 sgi_cpu_mask, struct kvm_vcpu *vcpu)
{
	unsigned long affinity;
	int level0;

	/*
	 * Split the current VCPU's MPIDR into affinity level 0 and the
	 * rest as this is what we have to compare against.
	 */
	affinity = kvm_vcpu_get_mpidr_aff(vcpu);
	level0 = MPIDR_AFFINITY_LEVEL(affinity, 0);
	affinity &= ~MPIDR_LEVEL_MASK;

	/* bail out if the upper three levels don't match */
	if (sgi_aff != affinity)
		return -1;

	/* Is this VCPU's bit set in the mask ? */
	if (!(sgi_cpu_mask & BIT(level0)))
		return -1;

	return level0;
}