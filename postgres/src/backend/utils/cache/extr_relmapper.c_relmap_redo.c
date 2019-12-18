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
struct TYPE_2__ {int nbytes; scalar_t__ dbid; int /*<<< orphan*/  tsid; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ xl_relmap_update ;
typedef  int uint8 ;
typedef  int /*<<< orphan*/  newmap ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  RelMapFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetDatabasePath (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  PANIC ; 
 int XLOG_RELMAP_UPDATE ; 
 int XLR_INFO_MASK ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecHasAnyBlockRefs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  write_relmap_file (int,int /*<<< orphan*/ *,int,int,int,scalar_t__,int /*<<< orphan*/ ,char*) ; 

void
relmap_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	/* Backup blocks are not used in relmap records */
	Assert(!XLogRecHasAnyBlockRefs(record));

	if (info == XLOG_RELMAP_UPDATE)
	{
		xl_relmap_update *xlrec = (xl_relmap_update *) XLogRecGetData(record);
		RelMapFile	newmap;
		char	   *dbpath;

		if (xlrec->nbytes != sizeof(RelMapFile))
			elog(PANIC, "relmap_redo: wrong size %u in relmap update record",
				 xlrec->nbytes);
		memcpy(&newmap, xlrec->data, sizeof(newmap));

		/* We need to construct the pathname for this database */
		dbpath = GetDatabasePath(xlrec->dbid, xlrec->tsid);

		/*
		 * Write out the new map and send sinval, but of course don't write a
		 * new WAL entry.  There's no surrounding transaction to tell to
		 * preserve files, either.
		 *
		 * There shouldn't be anyone else updating relmaps during WAL replay,
		 * so we don't bother to take the RelationMappingLock.  We would need
		 * to do so if load_relmap_file needed to interlock against writers.
		 */
		write_relmap_file((xlrec->dbid == InvalidOid), &newmap,
						  false, true, false,
						  xlrec->dbid, xlrec->tsid, dbpath);

		pfree(dbpath);
	}
	else
		elog(PANIC, "relmap_redo: unknown op code %u", info);
}