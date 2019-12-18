#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int contiguous_pages_dirty; int /*<<< orphan*/ * freelist; scalar_t__ free_pages; scalar_t__ contiguous_pages; scalar_t__ singleton_npages; scalar_t__ singleton_first_page; scalar_t__ btree_recycle_count; scalar_t__ btree_depth; int /*<<< orphan*/  btree_recycle; int /*<<< orphan*/  btree_root; int /*<<< orphan*/  self; } ;
typedef  size_t Size ;
typedef  TYPE_1__ FreePageSpanLeader ;
typedef  TYPE_1__ FreePageManager ;
typedef  TYPE_1__ FreePageBtree ;

/* Variables and functions */
 size_t FPM_NUM_FREELISTS ; 
 int /*<<< orphan*/  relptr_store (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
FreePageManagerInitialize(FreePageManager *fpm, char *base)
{
	Size		f;

	relptr_store(base, fpm->self, fpm);
	relptr_store(base, fpm->btree_root, (FreePageBtree *) NULL);
	relptr_store(base, fpm->btree_recycle, (FreePageSpanLeader *) NULL);
	fpm->btree_depth = 0;
	fpm->btree_recycle_count = 0;
	fpm->singleton_first_page = 0;
	fpm->singleton_npages = 0;
	fpm->contiguous_pages = 0;
	fpm->contiguous_pages_dirty = true;
#ifdef FPM_EXTRA_ASSERTS
	fpm->free_pages = 0;
#endif

	for (f = 0; f < FPM_NUM_FREELISTS; f++)
		relptr_store(base, fpm->freelist[f], (FreePageSpanLeader *) NULL);
}