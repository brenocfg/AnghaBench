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
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int HASH_NOLOCK ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

Buffer
_hash_getbuf_with_strategy(Relation rel, BlockNumber blkno,
						   int access, int flags,
						   BufferAccessStrategy bstrategy)
{
	Buffer		buf;

	if (blkno == P_NEW)
		elog(ERROR, "hash AM does not use P_NEW");

	buf = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL, bstrategy);

	if (access != HASH_NOLOCK)
		LockBuffer(buf, access);

	/* ref count and lock type are correct */

	_hash_checkpage(rel, buf, flags);

	return buf;
}