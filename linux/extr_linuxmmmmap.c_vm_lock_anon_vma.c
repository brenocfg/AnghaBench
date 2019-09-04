#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct anon_vma {TYPE_3__* root; } ;
struct TYPE_4__ {int /*<<< orphan*/  rb_node; } ;
struct TYPE_5__ {TYPE_1__ rb_root; } ;
struct TYPE_6__ {TYPE_2__ rb_root; int /*<<< orphan*/  rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ __test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  down_write_nest_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void vm_lock_anon_vma(struct mm_struct *mm, struct anon_vma *anon_vma)
{
	if (!test_bit(0, (unsigned long *) &anon_vma->root->rb_root.rb_root.rb_node)) {
		/*
		 * The LSB of head.next can't change from under us
		 * because we hold the mm_all_locks_mutex.
		 */
		down_write_nest_lock(&anon_vma->root->rwsem, &mm->mmap_sem);
		/*
		 * We can safely modify head.next after taking the
		 * anon_vma->root->rwsem. If some other vma in this mm shares
		 * the same anon_vma we won't take it again.
		 *
		 * No need of atomic instructions here, head.next
		 * can't change from under us thanks to the
		 * anon_vma->root->rwsem.
		 */
		if (__test_and_set_bit(0, (unsigned long *)
				       &anon_vma->root->rb_root.rb_root.rb_node))
			BUG();
	}
}