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
struct TYPE_6__ {int rd_refcnt; scalar_t__ rd_createSubid; scalar_t__ rd_newRelfilenodeSubid; scalar_t__ rd_isnailed; } ;
typedef  TYPE_1__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidSubTransactionId ; 
 int /*<<< orphan*/  IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  RelationClearRelation (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 scalar_t__ RelationHasReferenceCountZero (TYPE_1__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AtEOXact_cleanup(Relation relation, bool isCommit)
{
	/*
	 * The relcache entry's ref count should be back to its normal
	 * not-in-a-transaction state: 0 unless it's nailed in cache.
	 *
	 * In bootstrap mode, this is NOT true, so don't check it --- the
	 * bootstrap code expects relations to stay open across start/commit
	 * transaction calls.  (That seems bogus, but it's not worth fixing.)
	 *
	 * Note: ideally this check would be applied to every relcache entry, not
	 * just those that have eoxact work to do.  But it's not worth forcing a
	 * scan of the whole relcache just for this.  (Moreover, doing so would
	 * mean that assert-enabled testing never tests the hash_search code path
	 * above, which seems a bad idea.)
	 */
#ifdef USE_ASSERT_CHECKING
	if (!IsBootstrapProcessingMode())
	{
		int			expected_refcnt;

		expected_refcnt = relation->rd_isnailed ? 1 : 0;
		Assert(relation->rd_refcnt == expected_refcnt);
	}
#endif

	/*
	 * Is it a relation created in the current transaction?
	 *
	 * During commit, reset the flag to zero, since we are now out of the
	 * creating transaction.  During abort, simply delete the relcache entry
	 * --- it isn't interesting any longer.  (NOTE: if we have forgotten the
	 * new-ness of a new relation due to a forced cache flush, the entry will
	 * get deleted anyway by shared-cache-inval processing of the aborted
	 * pg_class insertion.)
	 */
	if (relation->rd_createSubid != InvalidSubTransactionId)
	{
		if (isCommit)
			relation->rd_createSubid = InvalidSubTransactionId;
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
			 * dangling pointer later.  Bleat, and mark it as not belonging to
			 * the current transaction.  Hopefully it'll get cleaned up
			 * eventually.  This must be just a WARNING to avoid
			 * error-during-error-recovery loops.
			 */
			relation->rd_createSubid = InvalidSubTransactionId;
			elog(WARNING, "cannot remove relcache entry for \"%s\" because it has nonzero refcount",
				 RelationGetRelationName(relation));
		}
	}

	/*
	 * Likewise, reset the hint about the relfilenode being new.
	 */
	relation->rd_newRelfilenodeSubid = InvalidSubTransactionId;
}