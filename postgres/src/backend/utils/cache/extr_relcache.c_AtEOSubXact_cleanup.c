#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rd_createSubid; scalar_t__ rd_newRelfilenodeSubid; } ;
typedef  scalar_t__ SubTransactionId ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 scalar_t__ InvalidSubTransactionId ; 
 int /*<<< orphan*/  RelationClearRelation (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 scalar_t__ RelationHasReferenceCountZero (TYPE_1__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AtEOSubXact_cleanup(Relation relation, bool isCommit,
					SubTransactionId mySubid, SubTransactionId parentSubid)
{
	/*
	 * Is it a relation created in the current subtransaction?
	 *
	 * During subcommit, mark it as belonging to the parent, instead. During
	 * subabort, simply delete the relcache entry.
	 */
	if (relation->rd_createSubid == mySubid)
	{
		if (isCommit)
			relation->rd_createSubid = parentSubid;
		else if (RelationHasReferenceCountZero(relation))
		{
			RelationClearRelation(relation, false);
			return;
		}
		else
		{
			/*
			 * Hmm, somewhere there's a (leaked?) reference to the relation.
			 * We daren't remove the entry for fear of dereferencing a
			 * dangling pointer later.  Bleat, and transfer it to the parent
			 * subtransaction so we can try again later.  This must be just a
			 * WARNING to avoid error-during-error-recovery loops.
			 */
			relation->rd_createSubid = parentSubid;
			elog(WARNING, "cannot remove relcache entry for \"%s\" because it has nonzero refcount",
				 RelationGetRelationName(relation));
		}
	}

	/*
	 * Likewise, update or drop any new-relfilenode-in-subtransaction hint.
	 */
	if (relation->rd_newRelfilenodeSubid == mySubid)
	{
		if (isCommit)
			relation->rd_newRelfilenodeSubid = parentSubid;
		else
			relation->rd_newRelfilenodeSubid = InvalidSubTransactionId;
	}
}