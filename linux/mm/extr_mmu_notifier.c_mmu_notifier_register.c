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
struct mmu_notifier {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int __mmu_notifier_register (struct mmu_notifier*,struct mm_struct*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int mmu_notifier_register(struct mmu_notifier *mn, struct mm_struct *mm)
{
	int ret;

	down_write(&mm->mmap_sem);
	ret = __mmu_notifier_register(mn, mm);
	up_write(&mm->mmap_sem);
	return ret;
}