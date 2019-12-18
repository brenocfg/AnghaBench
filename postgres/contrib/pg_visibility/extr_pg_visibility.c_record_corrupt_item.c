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
struct TYPE_3__ {int next; int count; int /*<<< orphan*/ * tids; } ;
typedef  TYPE_1__ corrupt_items ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
record_corrupt_item(corrupt_items *items, ItemPointer tid)
{
	/* enlarge output array if needed. */
	if (items->next >= items->count)
	{
		items->count *= 2;
		items->tids = repalloc(items->tids,
							   items->count * sizeof(ItemPointerData));
	}
	/* and add the new item */
	items->tids[items->next++] = *tid;
}