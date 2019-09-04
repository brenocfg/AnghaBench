#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; scalar_t__ vm_file; } ;
struct notifier_block {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int VM_EXEC ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  sync_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
munmap_notify(struct notifier_block *self, unsigned long val, void *data)
{
	unsigned long addr = (unsigned long)data;
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *mpnt;

	down_read(&mm->mmap_sem);

	mpnt = find_vma(mm, addr);
	if (mpnt && mpnt->vm_file && (mpnt->vm_flags & VM_EXEC)) {
		up_read(&mm->mmap_sem);
		/* To avoid latency problems, we only process the current CPU,
		 * hoping that most samples for the task are on this CPU
		 */
		sync_buffer(raw_smp_processor_id());
		return 0;
	}

	up_read(&mm->mmap_sem);
	return 0;
}