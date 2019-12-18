#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * ii_ExclusionStrats; int /*<<< orphan*/ * ii_ExclusionProcs; int /*<<< orphan*/ * ii_ExclusionOps; int /*<<< orphan*/ * ii_PredicateState; void* ii_Predicate; int /*<<< orphan*/  ii_ExpressionsState; void* ii_Expressions; } ;
struct TYPE_7__ {struct TYPE_7__* il_next; TYPE_2__* il_info; void* il_ind; void* il_heap; } ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  TYPE_1__ IndexList ;
typedef  TYPE_2__ IndexInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* ILHead ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIL ; 
 void* copyObject (void*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * nogc ; 
 scalar_t__ palloc (int) ; 

void
index_register(Oid heap,
			   Oid ind,
			   IndexInfo *indexInfo)
{
	IndexList  *newind;
	MemoryContext oldcxt;

	/*
	 * XXX mao 10/31/92 -- don't gc index reldescs, associated info at
	 * bootstrap time.  we'll declare the indexes now, but want to create them
	 * later.
	 */

	if (nogc == NULL)
		nogc = AllocSetContextCreate(NULL,
									 "BootstrapNoGC",
									 ALLOCSET_DEFAULT_SIZES);

	oldcxt = MemoryContextSwitchTo(nogc);

	newind = (IndexList *) palloc(sizeof(IndexList));
	newind->il_heap = heap;
	newind->il_ind = ind;
	newind->il_info = (IndexInfo *) palloc(sizeof(IndexInfo));

	memcpy(newind->il_info, indexInfo, sizeof(IndexInfo));
	/* expressions will likely be null, but may as well copy it */
	newind->il_info->ii_Expressions =
		copyObject(indexInfo->ii_Expressions);
	newind->il_info->ii_ExpressionsState = NIL;
	/* predicate will likely be null, but may as well copy it */
	newind->il_info->ii_Predicate =
		copyObject(indexInfo->ii_Predicate);
	newind->il_info->ii_PredicateState = NULL;
	/* no exclusion constraints at bootstrap time, so no need to copy */
	Assert(indexInfo->ii_ExclusionOps == NULL);
	Assert(indexInfo->ii_ExclusionProcs == NULL);
	Assert(indexInfo->ii_ExclusionStrats == NULL);

	newind->il_next = ILHead;
	ILHead = newind;

	MemoryContextSwitchTo(oldcxt);
}