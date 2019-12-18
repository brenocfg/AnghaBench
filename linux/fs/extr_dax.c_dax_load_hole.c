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
struct xa_state {int dummy; } ;
struct vm_fault {unsigned long address; int /*<<< orphan*/  vma; } ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAX_ZERO_PAGE ; 
 void* dax_insert_entry (struct xa_state*,struct address_space*,struct vm_fault*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_zero_pfn (unsigned long) ; 
 int /*<<< orphan*/  pfn_to_pfn_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dax_load_hole (struct inode*,struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmf_insert_mixed (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t dax_load_hole(struct xa_state *xas,
		struct address_space *mapping, void **entry,
		struct vm_fault *vmf)
{
	struct inode *inode = mapping->host;
	unsigned long vaddr = vmf->address;
	pfn_t pfn = pfn_to_pfn_t(my_zero_pfn(vaddr));
	vm_fault_t ret;

	*entry = dax_insert_entry(xas, mapping, vmf, *entry, pfn,
			DAX_ZERO_PAGE, false);

	ret = vmf_insert_mixed(vmf->vma, vaddr, pfn);
	trace_dax_load_hole(inode, vmf, ret);
	return ret;
}