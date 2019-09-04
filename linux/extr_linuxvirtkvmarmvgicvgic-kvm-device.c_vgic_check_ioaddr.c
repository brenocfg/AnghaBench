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
struct kvm {int dummy; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int E2BIG ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int /*<<< orphan*/  IS_VGIC_ADDR_UNDEF (int) ; 
 int KVM_PHYS_MASK ; 

int vgic_check_ioaddr(struct kvm *kvm, phys_addr_t *ioaddr,
		      phys_addr_t addr, phys_addr_t alignment)
{
	if (addr & ~KVM_PHYS_MASK)
		return -E2BIG;

	if (!IS_ALIGNED(addr, alignment))
		return -EINVAL;

	if (!IS_VGIC_ADDR_UNDEF(*ioaddr))
		return -EEXIST;

	return 0;
}