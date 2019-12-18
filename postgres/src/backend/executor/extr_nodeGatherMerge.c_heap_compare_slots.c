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
typedef  int int32 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_5__ {int gm_nkeys; TYPE_1__* gm_sortkeys; int /*<<< orphan*/ ** gm_slots; } ;
struct TYPE_4__ {int /*<<< orphan*/  ssup_attno; } ;
typedef  TYPE_1__* SortSupport ;
typedef  size_t SlotNumber ;
typedef  TYPE_2__ GatherMergeState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int ApplySortComparator (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 size_t DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVERT_COMPARE_RESULT (int) ; 
 int /*<<< orphan*/  TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int32
heap_compare_slots(Datum a, Datum b, void *arg)
{
	GatherMergeState *node = (GatherMergeState *) arg;
	SlotNumber	slot1 = DatumGetInt32(a);
	SlotNumber	slot2 = DatumGetInt32(b);

	TupleTableSlot *s1 = node->gm_slots[slot1];
	TupleTableSlot *s2 = node->gm_slots[slot2];
	int			nkey;

	Assert(!TupIsNull(s1));
	Assert(!TupIsNull(s2));

	for (nkey = 0; nkey < node->gm_nkeys; nkey++)
	{
		SortSupport sortKey = node->gm_sortkeys + nkey;
		AttrNumber	attno = sortKey->ssup_attno;
		Datum		datum1,
					datum2;
		bool		isNull1,
					isNull2;
		int			compare;

		datum1 = slot_getattr(s1, attno, &isNull1);
		datum2 = slot_getattr(s2, attno, &isNull2);

		compare = ApplySortComparator(datum1, isNull1,
									  datum2, isNull2,
									  sortKey);
		if (compare != 0)
		{
			INVERT_COMPARE_RESULT(compare);
			return compare;
		}
	}
	return 0;
}