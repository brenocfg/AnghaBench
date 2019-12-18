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
struct anon_vma {TYPE_1__* root; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anon_vma_cachep ; 
 int /*<<< orphan*/  anon_vma_lock_write (struct anon_vma*) ; 
 int /*<<< orphan*/  anon_vma_unlock_write (struct anon_vma*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct anon_vma*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ rwsem_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void anon_vma_free(struct anon_vma *anon_vma)
{
	VM_BUG_ON(atomic_read(&anon_vma->refcount));

	/*
	 * Synchronize against page_lock_anon_vma_read() such that
	 * we can safely hold the lock without the anon_vma getting
	 * freed.
	 *
	 * Relies on the full mb implied by the atomic_dec_and_test() from
	 * put_anon_vma() against the acquire barrier implied by
	 * down_read_trylock() from page_lock_anon_vma_read(). This orders:
	 *
	 * page_lock_anon_vma_read()	VS	put_anon_vma()
	 *   down_read_trylock()		  atomic_dec_and_test()
	 *   LOCK				  MB
	 *   atomic_read()			  rwsem_is_locked()
	 *
	 * LOCK should suffice since the actual taking of the lock must
	 * happen _before_ what follows.
	 */
	might_sleep();
	if (rwsem_is_locked(&anon_vma->root->rwsem)) {
		anon_vma_lock_write(anon_vma);
		anon_vma_unlock_write(anon_vma);
	}

	kmem_cache_free(anon_vma_cachep, anon_vma);
}