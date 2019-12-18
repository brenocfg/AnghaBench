#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_15__ {int /*<<< orphan*/  mdfd_vfd; } ;
struct TYPE_12__ {int /*<<< orphan*/  relNode; int /*<<< orphan*/  dbNode; int /*<<< orphan*/  spcNode; } ;
struct TYPE_13__ {int /*<<< orphan*/  backend; TYPE_1__ node; } ;
struct TYPE_14__ {TYPE_2__ smgr_rnode; } ;
typedef  TYPE_3__* SMgrRelation ;
typedef  TYPE_4__ MdfdVec ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_DISK_FULL ; 
 int /*<<< orphan*/  ERROR ; 
 int EXTENSION_CREATE_RECOVERY ; 
 int EXTENSION_FAIL ; 
 int /*<<< orphan*/  FilePathName (int /*<<< orphan*/ ) ; 
 int FileWrite (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int RELSEG_SIZE ; 
 int /*<<< orphan*/  SmgrIsTemp (TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SMGR_MD_WRITE_DONE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_SMGR_MD_WRITE_START (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_DATA_FILE_WRITE ; 
 TYPE_4__* _mdfd_getseg (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int,int /*<<< orphan*/ ,...) ; 
 int mdnblocks (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_dirty_segment (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

void
mdwrite(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum,
		char *buffer, bool skipFsync)
{
	off_t		seekpos;
	int			nbytes;
	MdfdVec    *v;

	/* This assert is too expensive to have on normally ... */
#ifdef CHECK_WRITE_VS_EXTEND
	Assert(blocknum < mdnblocks(reln, forknum));
#endif

	TRACE_POSTGRESQL_SMGR_MD_WRITE_START(forknum, blocknum,
										 reln->smgr_rnode.node.spcNode,
										 reln->smgr_rnode.node.dbNode,
										 reln->smgr_rnode.node.relNode,
										 reln->smgr_rnode.backend);

	v = _mdfd_getseg(reln, forknum, blocknum, skipFsync,
					 EXTENSION_FAIL | EXTENSION_CREATE_RECOVERY);

	seekpos = (off_t) BLCKSZ * (blocknum % ((BlockNumber) RELSEG_SIZE));

	Assert(seekpos < (off_t) BLCKSZ * RELSEG_SIZE);

	nbytes = FileWrite(v->mdfd_vfd, buffer, BLCKSZ, seekpos, WAIT_EVENT_DATA_FILE_WRITE);

	TRACE_POSTGRESQL_SMGR_MD_WRITE_DONE(forknum, blocknum,
										reln->smgr_rnode.node.spcNode,
										reln->smgr_rnode.node.dbNode,
										reln->smgr_rnode.node.relNode,
										reln->smgr_rnode.backend,
										nbytes,
										BLCKSZ);

	if (nbytes != BLCKSZ)
	{
		if (nbytes < 0)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not write block %u in file \"%s\": %m",
							blocknum, FilePathName(v->mdfd_vfd))));
		/* short write: complain appropriately */
		ereport(ERROR,
				(errcode(ERRCODE_DISK_FULL),
				 errmsg("could not write block %u in file \"%s\": wrote only %d of %d bytes",
						blocknum,
						FilePathName(v->mdfd_vfd),
						nbytes, BLCKSZ),
				 errhint("Check free disk space.")));
	}

	if (!skipFsync && !SmgrIsTemp(reln))
		register_dirty_segment(reln, forknum, v);
}