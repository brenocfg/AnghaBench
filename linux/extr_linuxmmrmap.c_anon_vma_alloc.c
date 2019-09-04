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
struct anon_vma {int degree; struct anon_vma* root; struct anon_vma* parent; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  anon_vma_cachep ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct anon_vma* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct anon_vma *anon_vma_alloc(void)
{
	struct anon_vma *anon_vma;

	anon_vma = kmem_cache_alloc(anon_vma_cachep, GFP_KERNEL);
	if (anon_vma) {
		atomic_set(&anon_vma->refcount, 1);
		anon_vma->degree = 1;	/* Reference for first vma */
		anon_vma->parent = anon_vma;
		/*
		 * Initialise the anon_vma root to point to itself. If called
		 * from fork, the root will be reset to the parents anon_vma.
		 */
		anon_vma->root = anon_vma;
	}

	return anon_vma;
}