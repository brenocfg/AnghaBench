#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rd_createSubid; scalar_t__ rd_newRelfilenodeSubid; } ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 scalar_t__ InvalidSubTransactionId ; 
 int /*<<< orphan*/  RelationClearRelation (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RelationDecrementReferenceCount (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationHasReferenceCountZero (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationIncrementReferenceCount (TYPE_1__*) ; 

__attribute__((used)) static void
RelationFlushRelation(Relation relation)
{
	if (relation->rd_createSubid != InvalidSubTransactionId ||
		relation->rd_newRelfilenodeSubid != InvalidSubTransactionId)
	{
		/*
		 * New relcache entries are always rebuilt, not flushed; else we'd
		 * forget the "new" status of the relation, which is a useful
		 * optimization to have.  Ditto for the new-relfilenode status.
		 *
		 * The rel could have zero refcnt here, so temporarily increment the
		 * refcnt to ensure it's safe to rebuild it.  We can assume that the
		 * current transaction has some lock on the rel already.
		 */
		RelationIncrementReferenceCount(relation);
		RelationClearRelation(relation, true);
		RelationDecrementReferenceCount(relation);
	}
	else
	{
		/*
		 * Pre-existing rels can be dropped from the relcache if not open.
		 */
		bool		rebuild = !RelationHasReferenceCountZero(relation);

		RelationClearRelation(relation, rebuild);
	}
}