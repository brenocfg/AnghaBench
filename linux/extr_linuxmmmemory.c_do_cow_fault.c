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
typedef  int vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  cow_page; int /*<<< orphan*/  memcg; int /*<<< orphan*/  page; int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VM_FAULT_DONE_COW ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_RETRY ; 
 int /*<<< orphan*/  __SetPageUptodate (int /*<<< orphan*/ ) ; 
 int __do_fault (struct vm_fault*) ; 
 int /*<<< orphan*/  alloc_page_vma (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int anon_vma_prepare (struct vm_area_struct*) ; 
 int /*<<< orphan*/  copy_user_highpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int finish_fault (struct vm_fault*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mem_cgroup_try_charge_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t do_cow_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	vm_fault_t ret;

	if (unlikely(anon_vma_prepare(vma)))
		return VM_FAULT_OOM;

	vmf->cow_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, vmf->address);
	if (!vmf->cow_page)
		return VM_FAULT_OOM;

	if (mem_cgroup_try_charge_delay(vmf->cow_page, vma->vm_mm, GFP_KERNEL,
				&vmf->memcg, false)) {
		put_page(vmf->cow_page);
		return VM_FAULT_OOM;
	}

	ret = __do_fault(vmf);
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		goto uncharge_out;
	if (ret & VM_FAULT_DONE_COW)
		return ret;

	copy_user_highpage(vmf->cow_page, vmf->page, vmf->address, vma);
	__SetPageUptodate(vmf->cow_page);

	ret |= finish_fault(vmf);
	unlock_page(vmf->page);
	put_page(vmf->page);
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		goto uncharge_out;
	return ret;
uncharge_out:
	mem_cgroup_cancel_charge(vmf->cow_page, vmf->memcg, false);
	put_page(vmf->cow_page);
	return ret;
}