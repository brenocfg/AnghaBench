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
struct vm_area_struct {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 unsigned long gfn_to_hva (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 unsigned long vma_kernel_pagesize (struct vm_area_struct*) ; 

unsigned long kvm_host_page_size(struct kvm *kvm, gfn_t gfn)
{
	struct vm_area_struct *vma;
	unsigned long addr, size;

	size = PAGE_SIZE;

	addr = gfn_to_hva(kvm, gfn);
	if (kvm_is_error_hva(addr))
		return PAGE_SIZE;

	down_read(&current->mm->mmap_sem);
	vma = find_vma(current->mm, addr);
	if (!vma)
		goto out;

	size = vma_kernel_pagesize(vma);

out:
	up_read(&current->mm->mmap_sem);

	return size;
}