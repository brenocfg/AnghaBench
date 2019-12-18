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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,scalar_t__) ; 
 int bms_first_member (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_tuple_attr_equals (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bitmapset *
HeapDetermineModifiedColumns(Relation relation, Bitmapset *interesting_cols,
							 HeapTuple oldtup, HeapTuple newtup)
{
	int			attnum;
	Bitmapset  *modified = NULL;

	while ((attnum = bms_first_member(interesting_cols)) >= 0)
	{
		attnum += FirstLowInvalidHeapAttributeNumber;

		if (!heap_tuple_attr_equals(RelationGetDescr(relation),
									attnum, oldtup, newtup))
			modified = bms_add_member(modified,
									  attnum - FirstLowInvalidHeapAttributeNumber);
	}

	return modified;
}