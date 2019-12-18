#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ts_id; } ;
typedef  TYPE_1__ xl_tblspc_drop_rec ;
struct TYPE_4__ {char* ts_path; int /*<<< orphan*/  ts_id; } ;
typedef  TYPE_2__ xl_tblspc_create_rec ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithTablespace (int /*<<< orphan*/ ) ; 
 scalar_t__ XLOG_TBLSPC_CREATE ; 
 scalar_t__ XLOG_TBLSPC_DROP ; 
 scalar_t__ XLR_INFO_MASK ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecHasAnyBlockRefs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_tablespace_directories (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_tablespace_directories (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

void
tblspc_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	/* Backup blocks are not used in tblspc records */
	Assert(!XLogRecHasAnyBlockRefs(record));

	if (info == XLOG_TBLSPC_CREATE)
	{
		xl_tblspc_create_rec *xlrec = (xl_tblspc_create_rec *) XLogRecGetData(record);
		char	   *location = xlrec->ts_path;

		create_tablespace_directories(location, xlrec->ts_id);
	}
	else if (info == XLOG_TBLSPC_DROP)
	{
		xl_tblspc_drop_rec *xlrec = (xl_tblspc_drop_rec *) XLogRecGetData(record);

		/*
		 * If we issued a WAL record for a drop tablespace it implies that
		 * there were no files in it at all when the DROP was done. That means
		 * that no permanent objects can exist in it at this point.
		 *
		 * It is possible for standby users to be using this tablespace as a
		 * location for their temporary files, so if we fail to remove all
		 * files then do conflict processing and try again, if currently
		 * enabled.
		 *
		 * Other possible reasons for failure include bollixed file
		 * permissions on a standby server when they were okay on the primary,
		 * etc etc. There's not much we can do about that, so just remove what
		 * we can and press on.
		 */
		if (!destroy_tablespace_directories(xlrec->ts_id, true))
		{
			ResolveRecoveryConflictWithTablespace(xlrec->ts_id);

			/*
			 * If we did recovery processing then hopefully the backends who
			 * wrote temp files should have cleaned up and exited by now.  So
			 * retry before complaining.  If we fail again, this is just a LOG
			 * condition, because it's not worth throwing an ERROR for (as
			 * that would crash the database and require manual intervention
			 * before we could get past this WAL record on restart).
			 */
			if (!destroy_tablespace_directories(xlrec->ts_id, true))
				ereport(LOG,
						(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						 errmsg("directories for tablespace %u could not be removed",
								xlrec->ts_id),
						 errhint("You can remove the directories manually if necessary.")));
		}
	}
	else
		elog(PANIC, "tblspc_redo: unknown op code %u", info);
}