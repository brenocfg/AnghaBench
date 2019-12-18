#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_WRITE ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  RBM_ZERO_AND_LOCK ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RelationGetNumberOfBlocksInFork (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_pageinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

Buffer
_hash_getnewbuf(Relation rel, BlockNumber blkno, ForkNumber forkNum)
{
	BlockNumber nblocks = RelationGetNumberOfBlocksInFork(rel, forkNum);
	Buffer		buf;

	if (blkno == P_NEW)
		elog(ERROR, "hash AM does not use P_NEW");
	if (blkno > nblocks)
		elog(ERROR, "access to noncontiguous page in hash index \"%s\"",
			 RelationGetRelationName(rel));

	/* smgr insists we use P_NEW to extend the relation */
	if (blkno == nblocks)
	{
		buf = ReadBufferExtended(rel, forkNum, P_NEW, RBM_NORMAL, NULL);
		if (BufferGetBlockNumber(buf) != blkno)
			elog(ERROR, "unexpected hash relation size: %u, should be %u",
				 BufferGetBlockNumber(buf), blkno);
		LockBuffer(buf, HASH_WRITE);
	}
	else
	{
		buf = ReadBufferExtended(rel, forkNum, blkno, RBM_ZERO_AND_LOCK,
								 NULL);
	}

	/* ref count and lock type are correct */

	/* initialize the page */
	_hash_pageinit(BufferGetPage(buf), BufferGetPageSize(buf));

	return buf;
}