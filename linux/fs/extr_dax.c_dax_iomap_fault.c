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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int dummy; } ;
struct iomap_ops {int dummy; } ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  enum page_entry_size { ____Placeholder_page_entry_size } page_entry_size ;

/* Variables and functions */
#define  PE_SIZE_PMD 129 
#define  PE_SIZE_PTE 128 
 int /*<<< orphan*/  VM_FAULT_FALLBACK ; 
 int /*<<< orphan*/  dax_iomap_pmd_fault (struct vm_fault*,int /*<<< orphan*/ *,struct iomap_ops const*) ; 
 int /*<<< orphan*/  dax_iomap_pte_fault (struct vm_fault*,int /*<<< orphan*/ *,int*,struct iomap_ops const*) ; 

vm_fault_t dax_iomap_fault(struct vm_fault *vmf, enum page_entry_size pe_size,
		    pfn_t *pfnp, int *iomap_errp, const struct iomap_ops *ops)
{
	switch (pe_size) {
	case PE_SIZE_PTE:
		return dax_iomap_pte_fault(vmf, pfnp, iomap_errp, ops);
	case PE_SIZE_PMD:
		return dax_iomap_pmd_fault(vmf, pfnp, ops);
	default:
		return VM_FAULT_FALLBACK;
	}
}