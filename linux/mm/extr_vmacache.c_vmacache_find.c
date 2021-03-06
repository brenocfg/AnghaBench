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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
struct TYPE_3__ {struct vm_area_struct** vmas; } ;
struct TYPE_4__ {TYPE_1__ vmacache; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMACACHE_FIND_CALLS ; 
 int /*<<< orphan*/  VMACACHE_FIND_HITS ; 
 int VMACACHE_HASH (unsigned long) ; 
 int VMACACHE_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  count_vm_vmacache_event (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  vmacache_valid (struct mm_struct*) ; 

struct vm_area_struct *vmacache_find(struct mm_struct *mm, unsigned long addr)
{
	int idx = VMACACHE_HASH(addr);
	int i;

	count_vm_vmacache_event(VMACACHE_FIND_CALLS);

	if (!vmacache_valid(mm))
		return NULL;

	for (i = 0; i < VMACACHE_SIZE; i++) {
		struct vm_area_struct *vma = current->vmacache.vmas[idx];

		if (vma) {
#ifdef CONFIG_DEBUG_VM_VMACACHE
			if (WARN_ON_ONCE(vma->vm_mm != mm))
				break;
#endif
			if (vma->vm_start <= addr && vma->vm_end > addr) {
				count_vm_vmacache_event(VMACACHE_FIND_HITS);
				return vma;
			}
		}
		if (++idx == VMACACHE_SIZE)
			idx = 0;
	}

	return NULL;
}