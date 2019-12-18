#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  tree_walk; } ;
struct TYPE_4__ {int count; scalar_t__ shouldSort; int /*<<< orphan*/ * list; int /*<<< orphan*/  category; int /*<<< orphan*/  key; int /*<<< orphan*/  attnum; } ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  TYPE_1__ GinEntryAccumulator ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsortCompareItemPointers ; 
 scalar_t__ rbt_iterate (int /*<<< orphan*/ *) ; 

ItemPointerData *
ginGetBAEntry(BuildAccumulator *accum,
			  OffsetNumber *attnum, Datum *key, GinNullCategory *category,
			  uint32 *n)
{
	GinEntryAccumulator *entry;
	ItemPointerData *list;

	entry = (GinEntryAccumulator *) rbt_iterate(&accum->tree_walk);

	if (entry == NULL)
		return NULL;			/* no more entries */

	*attnum = entry->attnum;
	*key = entry->key;
	*category = entry->category;
	list = entry->list;
	*n = entry->count;

	Assert(list != NULL && entry->count > 0);

	if (entry->shouldSort && entry->count > 1)
		qsort(list, entry->count, sizeof(ItemPointerData),
			  qsortCompareItemPointers);

	return list;
}