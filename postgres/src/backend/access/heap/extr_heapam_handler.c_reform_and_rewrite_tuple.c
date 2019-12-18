#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {scalar_t__ attisdropped; } ;
struct TYPE_7__ {int natts; } ;
typedef  int /*<<< orphan*/  RewriteState ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_form_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewrite_heap_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reform_and_rewrite_tuple(HeapTuple tuple,
						 Relation OldHeap, Relation NewHeap,
						 Datum *values, bool *isnull, RewriteState rwstate)
{
	TupleDesc	oldTupDesc = RelationGetDescr(OldHeap);
	TupleDesc	newTupDesc = RelationGetDescr(NewHeap);
	HeapTuple	copiedTuple;
	int			i;

	heap_deform_tuple(tuple, oldTupDesc, values, isnull);

	/* Be sure to null out any dropped columns */
	for (i = 0; i < newTupDesc->natts; i++)
	{
		if (TupleDescAttr(newTupDesc, i)->attisdropped)
			isnull[i] = true;
	}

	copiedTuple = heap_form_tuple(newTupDesc, values, isnull);

	/* The heap rewrite module does the rest */
	rewrite_heap_tuple(rwstate, tuple, copiedTuple);

	heap_freetuple(copiedTuple);
}