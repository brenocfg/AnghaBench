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
struct TYPE_5__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  IndexUniqueCheck ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int _bt_doinsert (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* index_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

bool
btinsert(Relation rel, Datum *values, bool *isnull,
		 ItemPointer ht_ctid, Relation heapRel,
		 IndexUniqueCheck checkUnique,
		 IndexInfo *indexInfo)
{
	bool		result;
	IndexTuple	itup;

	/* generate an index tuple */
	itup = index_form_tuple(RelationGetDescr(rel), values, isnull);
	itup->t_tid = *ht_ctid;

	result = _bt_doinsert(rel, itup, checkUnique, heapRel);

	pfree(itup);

	return result;
}