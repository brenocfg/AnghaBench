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
typedef  int /*<<< orphan*/  SubTransactionId ;
typedef  TYPE_1__ RelIdCacheEnt ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AtEOSubXact_cleanup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  RelationIdCache ; 
 int /*<<< orphan*/ * eoxact_list ; 
 int eoxact_list_len ; 
 scalar_t__ eoxact_list_overflowed ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

void
AtEOSubXact_RelationCache(bool isCommit, SubTransactionId mySubid,
						  SubTransactionId parentSubid)
{
	HASH_SEQ_STATUS status;
	RelIdCacheEnt *idhentry;
	int			i;

	/*
	 * Unless the eoxact_list[] overflowed, we only need to examine the rels
	 * listed in it.  Otherwise fall back on a hash_seq_search scan.  Same
	 * logic as in AtEOXact_RelationCache.
	 */
	if (eoxact_list_overflowed)
	{
		hash_seq_init(&status, RelationIdCache);
		while ((idhentry = (RelIdCacheEnt *) hash_seq_search(&status)) != NULL)
		{
			AtEOSubXact_cleanup(idhentry->reldesc, isCommit,
								mySubid, parentSubid);
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
				AtEOSubXact_cleanup(idhentry->reldesc, isCommit,
									mySubid, parentSubid);
		}
	}

	/* Don't reset the list; we still need more cleanup later */
}