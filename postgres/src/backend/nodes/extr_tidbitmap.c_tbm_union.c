#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pagetable_iterator ;
struct TYPE_5__ {scalar_t__ nentries; scalar_t__ status; int /*<<< orphan*/  pagetable; int /*<<< orphan*/  entry1; int /*<<< orphan*/  iterating; } ;
typedef  TYPE_1__ TIDBitmap ;
typedef  int /*<<< orphan*/  PagetableEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ TBM_HASH ; 
 scalar_t__ TBM_ONE_PAGE ; 
 int /*<<< orphan*/ * pagetable_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagetable_start_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_union_page (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
tbm_union(TIDBitmap *a, const TIDBitmap *b)
{
	Assert(!a->iterating);
	/* Nothing to do if b is empty */
	if (b->nentries == 0)
		return;
	/* Scan through chunks and pages in b, merge into a */
	if (b->status == TBM_ONE_PAGE)
		tbm_union_page(a, &b->entry1);
	else
	{
		pagetable_iterator i;
		PagetableEntry *bpage;

		Assert(b->status == TBM_HASH);
		pagetable_start_iterate(b->pagetable, &i);
		while ((bpage = pagetable_iterate(b->pagetable, &i)) != NULL)
			tbm_union_page(a, bpage);
	}
}