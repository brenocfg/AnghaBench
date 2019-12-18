#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* rd_indam; } ;
struct TYPE_8__ {int (* aminsert ) (TYPE_2__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ampredlocks; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  IndexUniqueCheck ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REL_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  RELATION_CHECKS ; 
 int /*<<< orphan*/  aminsert ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
index_insert(Relation indexRelation,
			 Datum *values,
			 bool *isnull,
			 ItemPointer heap_t_ctid,
			 Relation heapRelation,
			 IndexUniqueCheck checkUnique,
			 IndexInfo *indexInfo)
{
	RELATION_CHECKS;
	CHECK_REL_PROCEDURE(aminsert);

	if (!(indexRelation->rd_indam->ampredlocks))
		CheckForSerializableConflictIn(indexRelation,
									   (HeapTuple) NULL,
									   InvalidBuffer);

	return indexRelation->rd_indam->aminsert(indexRelation, values, isnull,
											 heap_t_ctid, heapRelation,
											 checkUnique, indexInfo);
}