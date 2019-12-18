#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_10__ {int /*<<< orphan*/  node; } ;
struct TYPE_12__ {TYPE_1__ smgr_rnode; } ;
struct TYPE_11__ {TYPE_3__* rd_smgr; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BufMappingPartitionLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufTableHashCode (int /*<<< orphan*/ *) ; 
 int BufTableLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INIT_BUFFERTAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  LocalPrefetchBuffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_2__*) ; 
 scalar_t__ RelationUsesLocalBuffers (TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  smgrprefetch (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PrefetchBuffer(Relation reln, ForkNumber forkNum, BlockNumber blockNum)
{
#ifdef USE_PREFETCH
	Assert(RelationIsValid(reln));
	Assert(BlockNumberIsValid(blockNum));

	/* Open it at the smgr level if not already done */
	RelationOpenSmgr(reln);

	if (RelationUsesLocalBuffers(reln))
	{
		/* see comments in ReadBufferExtended */
		if (RELATION_IS_OTHER_TEMP(reln))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot access temporary tables of other sessions")));

		/* pass it off to localbuf.c */
		LocalPrefetchBuffer(reln->rd_smgr, forkNum, blockNum);
	}
	else
	{
		BufferTag	newTag;		/* identity of requested block */
		uint32		newHash;	/* hash value for newTag */
		LWLock	   *newPartitionLock;	/* buffer partition lock for it */
		int			buf_id;

		/* create a tag so we can lookup the buffer */
		INIT_BUFFERTAG(newTag, reln->rd_smgr->smgr_rnode.node,
					   forkNum, blockNum);

		/* determine its hash code and partition lock ID */
		newHash = BufTableHashCode(&newTag);
		newPartitionLock = BufMappingPartitionLock(newHash);

		/* see if the block is in the buffer pool already */
		LWLockAcquire(newPartitionLock, LW_SHARED);
		buf_id = BufTableLookup(&newTag, newHash);
		LWLockRelease(newPartitionLock);

		/* If not in buffers, initiate prefetch */
		if (buf_id < 0)
			smgrprefetch(reln->rd_smgr, forkNum, blockNum);

		/*
		 * If the block *is* in buffers, we do nothing.  This is not really
		 * ideal: the block might be just about to be evicted, which would be
		 * stupid since we know we are going to need it soon.  But the only
		 * easy answer is to bump the usage_count, which does not seem like a
		 * great solution: when the caller does ultimately touch the block,
		 * usage_count would get bumped again, resulting in too much
		 * favoritism for blocks that are involved in a prefetch sequence. A
		 * real fix would involve some additional per-buffer state, and it's
		 * not clear that there's enough of a problem to justify that.
		 */
	}
#endif							/* USE_PREFETCH */
}