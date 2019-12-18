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
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {int ReadRecPtr; int max_block_id; } ;
typedef  TYPE_1__ XLogReaderState ;
typedef  size_t RmgrId ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ ForkNumber ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 scalar_t__ MAIN_FORKNUM ; 
 size_t RM_DBASE_ID ; 
 size_t RM_SMGR_ID ; 
 int /*<<< orphan*/ * RmgrNames ; 
 scalar_t__ XLOG_DBASE_CREATE ; 
 scalar_t__ XLOG_DBASE_DROP ; 
 scalar_t__ XLOG_SMGR_CREATE ; 
 scalar_t__ XLOG_SMGR_TRUNCATE ; 
 scalar_t__ XLR_INFO_MASK ; 
 scalar_t__ XLR_SPECIAL_REL_UPDATE ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_1__*,int,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (TYPE_1__*) ; 
 size_t XLogRecGetRmid (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  process_block_change (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extractPageInfo(XLogReaderState *record)
{
	int			block_id;
	RmgrId		rmid = XLogRecGetRmid(record);
	uint8		info = XLogRecGetInfo(record);
	uint8		rminfo = info & ~XLR_INFO_MASK;

	/* Is this a special record type that I recognize? */

	if (rmid == RM_DBASE_ID && rminfo == XLOG_DBASE_CREATE)
	{
		/*
		 * New databases can be safely ignored. It won't be present in the
		 * source system, so it will be deleted. There's one corner-case,
		 * though: if a new, different, database is also created in the source
		 * system, we'll see that the files already exist and not copy them.
		 * That's OK, though; WAL replay of creating the new database, from
		 * the source systems's WAL, will re-copy the new database,
		 * overwriting the database created in the target system.
		 */
	}
	else if (rmid == RM_DBASE_ID && rminfo == XLOG_DBASE_DROP)
	{
		/*
		 * An existing database was dropped. We'll see that the files don't
		 * exist in the target data dir, and copy them in toto from the source
		 * system. No need to do anything special here.
		 */
	}
	else if (rmid == RM_SMGR_ID && rminfo == XLOG_SMGR_CREATE)
	{
		/*
		 * We can safely ignore these. The file will be removed from the
		 * target, if it doesn't exist in source system. If a file with same
		 * name is created in source system, too, there will be WAL records
		 * for all the blocks in it.
		 */
	}
	else if (rmid == RM_SMGR_ID && rminfo == XLOG_SMGR_TRUNCATE)
	{
		/*
		 * We can safely ignore these. When we compare the sizes later on,
		 * we'll notice that they differ, and copy the missing tail from
		 * source system.
		 */
	}
	else if (info & XLR_SPECIAL_REL_UPDATE)
	{
		/*
		 * This record type modifies a relation file in some special way, but
		 * we don't recognize the type. That's bad - we don't know how to
		 * track that change.
		 */
		pg_fatal("WAL record modifies a relation, but record type is not recognized: "
				 "lsn: %X/%X, rmgr: %s, info: %02X",
				 (uint32) (record->ReadRecPtr >> 32), (uint32) (record->ReadRecPtr),
				 RmgrNames[rmid], info);
	}

	for (block_id = 0; block_id <= record->max_block_id; block_id++)
	{
		RelFileNode rnode;
		ForkNumber	forknum;
		BlockNumber blkno;

		if (!XLogRecGetBlockTag(record, block_id, &rnode, &forknum, &blkno))
			continue;

		/* We only care about the main fork; others are copied in toto */
		if (forknum != MAIN_FORKNUM)
			continue;

		process_block_change(forknum, rnode, blkno);
	}
}