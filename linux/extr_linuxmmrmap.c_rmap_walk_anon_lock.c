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
struct rmap_walk_control {struct anon_vma* (* anon_lock ) (struct page*) ;} ;
struct page {int dummy; } ;
struct anon_vma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  anon_vma_lock_read (struct anon_vma*) ; 
 struct anon_vma* page_anon_vma (struct page*) ; 
 struct anon_vma* stub1 (struct page*) ; 

__attribute__((used)) static struct anon_vma *rmap_walk_anon_lock(struct page *page,
					struct rmap_walk_control *rwc)
{
	struct anon_vma *anon_vma;

	if (rwc->anon_lock)
		return rwc->anon_lock(page);

	/*
	 * Note: remove_migration_ptes() cannot use page_lock_anon_vma_read()
	 * because that depends on page_mapped(); but not all its usages
	 * are holding mmap_sem. Users without mmap_sem are required to
	 * take a reference count to prevent the anon_vma disappearing
	 */
	anon_vma = page_anon_vma(page);
	if (!anon_vma)
		return NULL;

	anon_vma_lock_read(anon_vma);
	return anon_vma;
}