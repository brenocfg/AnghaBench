#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  reldesc; } ;
typedef  TYPE_1__ RelIdCacheEnt ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOXact_cleanup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * EOXactTupleDescArray ; 
 scalar_t__ EOXactTupleDescArrayLen ; 
 int /*<<< orphan*/  FreeTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int NextEOXactTupleDescNum ; 
 int /*<<< orphan*/  RelationIdCache ; 
 int /*<<< orphan*/ * eoxact_list ; 
 int eoxact_list_len ; 
 int eoxact_list_overflowed ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

void
AtEOXact_RelationCache(bool isCommit)
{
	HASH_SEQ_STATUS status;
	RelIdCacheEnt *idhentry;
	int			i;

	/*
	 * Unless the eoxact_list[] overflowed, we only need to examine the rels
	 * listed in it.  Otherwise fall back on a hash_seq_search scan.
	 *
	 * For simplicity, eoxact_list[] entries are not deleted till end of
	 * top-level transaction, even though we could remove them at
	 * subtransaction end in some cases, or remove relations from the list if
	 * they are cleared for other reasons.  Therefore we should expect the
	 * case that list entries are not found in the hashtable; if not, there's
	 * nothing to do for them.
	 */
	if (eoxact_list_overflowed)
	{
		hash_seq_init(&status, RelationIdCache);
		while ((idhentry = (RelIdCacheEnt *) hash_seq_search(&status)) != NULL)
		{
			AtEOXact_cleanup(idhentry->reldesc, isCommit);
		}
	}
	else
	{
		for (i = 0; i < eoxact_list_len; i++)
		{
			idhentry = (RelIdCacheEnt *) hash_search(RelationIdCache,
													 (void *) &eoxact_list[i],
													 HASH_FIND,
													 NULL);
			if (idhentry != NULL)
				AtEOXact_cleanup(idhentry->reldesc, isCommit);
		}
	}

	if (EOXactTupleDescArrayLen > 0)
	{
		Assert(EOXactTupleDescArray != NULL);
		for (i = 0; i < NextEOXactTupleDescNum; i++)
			FreeTupleDesc(EOXactTupleDescArray[i]);
		pfree(EOXactTupleDescArray);
		EOXactTupleDescArray = NULL;
	}

	/* Now we're out of the transaction and can clear the lists */
	eoxact_list_len = 0;
	eoxact_list_overflowed = false;
	NextEOXactTupleDescNum = 0;
	EOXactTupleDescArrayLen = 0;
}