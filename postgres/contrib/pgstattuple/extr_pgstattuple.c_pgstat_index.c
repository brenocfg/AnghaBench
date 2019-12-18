#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_5__ {int table_len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ pgstattuple_type ;
typedef  int /*<<< orphan*/  (* pgstat_page ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BAS_BULKREAD ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  GetAccessStrategy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pgstattuple_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
pgstat_index(Relation rel, BlockNumber start, pgstat_page pagefn,
			 FunctionCallInfo fcinfo)
{
	BlockNumber nblocks;
	BlockNumber blkno;
	BufferAccessStrategy bstrategy;
	pgstattuple_type stat = {0};

	/* prepare access strategy for this index */
	bstrategy = GetAccessStrategy(BAS_BULKREAD);

	blkno = start;
	for (;;)
	{
		/* Get the current relation length */
		LockRelationForExtension(rel, ExclusiveLock);
		nblocks = RelationGetNumberOfBlocks(rel);
		UnlockRelationForExtension(rel, ExclusiveLock);

		/* Quit if we've scanned the whole relation */
		if (blkno >= nblocks)
		{
			stat.table_len = (uint64) nblocks * BLCKSZ;

			break;
		}

		for (; blkno < nblocks; blkno++)
		{
			CHECK_FOR_INTERRUPTS();

			pagefn(&stat, rel, blkno, bstrategy);
		}
	}

	relation_close(rel, AccessShareLock);

	return build_pgstattuple_type(&stat, fcinfo);
}