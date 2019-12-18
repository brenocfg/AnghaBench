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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 scalar_t__ __kvm_cpu_uses_extended_idmap () ; 
 int /*<<< orphan*/  hyp_pgd ; 
 int /*<<< orphan*/  merged_hyp_pgd ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

phys_addr_t kvm_mmu_get_httbr(void)
{
	if (__kvm_cpu_uses_extended_idmap())
		return virt_to_phys(merged_hyp_pgd);
	else
		return virt_to_phys(hyp_pgd);
}