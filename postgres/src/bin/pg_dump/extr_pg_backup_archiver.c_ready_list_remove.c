#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TocEntry ;
struct TYPE_3__ {int first_te; int last_te; int /*<<< orphan*/ ** tes; } ;
typedef  TYPE_1__ ParallelReadyList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void
ready_list_remove(ParallelReadyList *ready_list, int i)
{
	int			f = ready_list->first_te;

	Assert(i >= f && i <= ready_list->last_te);

	/*
	 * In the typical case where the item to be removed is the first ready
	 * entry, we need only increment first_te to remove it.  Otherwise, move
	 * the entries before it to compact the list.  (This preserves sortedness,
	 * if any.)  We could alternatively move the entries after i, but there
	 * are typically many more of those.
	 */
	if (i > f)
	{
		TocEntry  **first_te_ptr = &ready_list->tes[f];

		memmove(first_te_ptr + 1, first_te_ptr, (i - f) * sizeof(TocEntry *));
	}
	ready_list->first_te++;
}