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
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long BIT (scalar_t__) ; 
 int ENOMEM ; 
 size_t PAGE_ALIGN (size_t) ; 
 scalar_t__ VA_BITS ; 
 int __create_hyp_mappings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __kvm_cpu_uses_extended_idmap () ; 
 int /*<<< orphan*/  __kvm_idmap_ptrs_per_pgd () ; 
 int /*<<< orphan*/  __phys_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * boot_hyp_pgd ; 
 int /*<<< orphan*/ * hyp_pgd ; 
 size_t io_map_base ; 
 int /*<<< orphan*/  kvm_hyp_pgd_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __create_hyp_private_mapping(phys_addr_t phys_addr, size_t size,
					unsigned long *haddr, pgprot_t prot)
{
	pgd_t *pgd = hyp_pgd;
	unsigned long base;
	int ret = 0;

	mutex_lock(&kvm_hyp_pgd_mutex);

	/*
	 * This assumes that we we have enough space below the idmap
	 * page to allocate our VAs. If not, the check below will
	 * kick. A potential alternative would be to detect that
	 * overflow and switch to an allocation above the idmap.
	 *
	 * The allocated size is always a multiple of PAGE_SIZE.
	 */
	size = PAGE_ALIGN(size + offset_in_page(phys_addr));
	base = io_map_base - size;

	/*
	 * Verify that BIT(VA_BITS - 1) hasn't been flipped by
	 * allocating the new area, as it would indicate we've
	 * overflowed the idmap/IO address range.
	 */
	if ((base ^ io_map_base) & BIT(VA_BITS - 1))
		ret = -ENOMEM;
	else
		io_map_base = base;

	mutex_unlock(&kvm_hyp_pgd_mutex);

	if (ret)
		goto out;

	if (__kvm_cpu_uses_extended_idmap())
		pgd = boot_hyp_pgd;

	ret = __create_hyp_mappings(pgd, __kvm_idmap_ptrs_per_pgd(),
				    base, base + size,
				    __phys_to_pfn(phys_addr), prot);
	if (ret)
		goto out;

	*haddr = base + offset_in_page(phys_addr);

out:
	return ret;
}