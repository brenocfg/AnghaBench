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
struct mm_struct {int dummy; } ;
struct mm_slot {int /*<<< orphan*/  mm_node; int /*<<< orphan*/  hash; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mm_slot (struct mm_slot*) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khugepaged_mm_lock ; 
 scalar_t__ khugepaged_test_exit (struct mm_struct*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 

__attribute__((used)) static void collect_mm_slot(struct mm_slot *mm_slot)
{
	struct mm_struct *mm = mm_slot->mm;

	lockdep_assert_held(&khugepaged_mm_lock);

	if (khugepaged_test_exit(mm)) {
		/* free mm_slot */
		hash_del(&mm_slot->hash);
		list_del(&mm_slot->mm_node);

		/*
		 * Not strictly needed because the mm exited already.
		 *
		 * clear_bit(MMF_VM_HUGEPAGE, &mm->flags);
		 */

		/* khugepaged_mm_lock actually not necessary for the below */
		free_mm_slot(mm_slot);
		mmdrop(mm);
	}
}