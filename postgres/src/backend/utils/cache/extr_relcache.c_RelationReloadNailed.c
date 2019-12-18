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
struct TYPE_8__ {scalar_t__ relkind; } ;
struct TYPE_7__ {int rd_isvalid; int rd_refcnt; TYPE_2__* rd_rel; int /*<<< orphan*/  rd_isnailed; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASS_TUPLE_SIZE ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 scalar_t__ RELKIND_INDEX ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationInitPhysicalAddr (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationReloadIndexInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  ScanPgRelation (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ criticalRelcachesBuilt ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RelationReloadNailed(Relation relation)
{
	Assert(relation->rd_isnailed);

	/*
	 * Redo RelationInitPhysicalAddr in case it is a mapped relation whose
	 * mapping changed.
	 */
	RelationInitPhysicalAddr(relation);

	/* flag as needing to be revalidated */
	relation->rd_isvalid = false;

	/*
	 * Can only reread catalog contents if in a transaction.  If the relation
	 * is currently open (not counting the nailed refcount), do so
	 * immediately. Otherwise we've already marked the entry as possibly
	 * invalid, and it'll be fixed when next opened.
	 */
	if (!IsTransactionState() || relation->rd_refcnt <= 1)
		return;

	if (relation->rd_rel->relkind == RELKIND_INDEX)
	{
		/*
		 * If it's a nailed-but-not-mapped index, then we need to re-read the
		 * pg_class row to see if its relfilenode changed.
		 */
		RelationReloadIndexInfo(relation);
	}
	else
	{
		/*
		 * Reload a non-index entry.  We can't easily do so if relcaches
		 * aren't yet built, but that's fine because at that stage the
		 * attributes that need to be current (like relfrozenxid) aren't yet
		 * accessed.  To ensure the entry will later be revalidated, we leave
		 * it in invalid state, but allow use (cf. RelationIdGetRelation()).
		 */
		if (criticalRelcachesBuilt)
		{
			HeapTuple	pg_class_tuple;
			Form_pg_class relp;

			/*
			 * NB: Mark the entry as valid before starting to scan, to avoid
			 * self-recursion when re-building pg_class.
			 */
			relation->rd_isvalid = true;

			pg_class_tuple = ScanPgRelation(RelationGetRelid(relation),
											true, false);
			relp = (Form_pg_class) GETSTRUCT(pg_class_tuple);
			memcpy(relation->rd_rel, relp, CLASS_TUPLE_SIZE);
			heap_freetuple(pg_class_tuple);

			/*
			 * Again mark as valid, to protect against concurrently arriving
			 * invalidations.
			 */
			relation->rd_isvalid = true;
		}
	}
}