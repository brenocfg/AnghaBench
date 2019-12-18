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
typedef  scalar_t__ XLogSegNo ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TimeLineID ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int InArchiveRecovery ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LOG ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  RECOVERY_SIGNAL_FILE ; 
 int /*<<< orphan*/  STANDBY_SIGNAL_FILE ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  UpdateMinRecoveryPoint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLByteToPrevSeg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLByteToSeg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogArchiveCleanup (char*) ; 
 int /*<<< orphan*/  XLogFileCopy (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int XLogFileInit (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogFileNameP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XLogSegmentOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  durable_unlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int readFile ; 
 scalar_t__ recovery_signal_file_found ; 
 scalar_t__ standby_signal_file_found ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
exitArchiveRecovery(TimeLineID endTLI, XLogRecPtr endOfLog)
{
	char		xlogfname[MAXFNAMELEN];
	XLogSegNo	endLogSegNo;
	XLogSegNo	startLogSegNo;

	/* we always switch to a new timeline after archive recovery */
	Assert(endTLI != ThisTimeLineID);

	/*
	 * We are no longer in archive recovery state.
	 */
	InArchiveRecovery = false;

	/*
	 * Update min recovery point one last time.
	 */
	UpdateMinRecoveryPoint(InvalidXLogRecPtr, true);

	/*
	 * If the ending log segment is still open, close it (to avoid problems on
	 * Windows with trying to rename or delete an open file).
	 */
	if (readFile >= 0)
	{
		close(readFile);
		readFile = -1;
	}

	/*
	 * Calculate the last segment on the old timeline, and the first segment
	 * on the new timeline. If the switch happens in the middle of a segment,
	 * they are the same, but if the switch happens exactly at a segment
	 * boundary, startLogSegNo will be endLogSegNo + 1.
	 */
	XLByteToPrevSeg(endOfLog, endLogSegNo, wal_segment_size);
	XLByteToSeg(endOfLog, startLogSegNo, wal_segment_size);

	/*
	 * Initialize the starting WAL segment for the new timeline. If the switch
	 * happens in the middle of a segment, copy data from the last WAL segment
	 * of the old timeline up to the switch point, to the starting WAL segment
	 * on the new timeline.
	 */
	if (endLogSegNo == startLogSegNo)
	{
		/*
		 * Make a copy of the file on the new timeline.
		 *
		 * Writing WAL isn't allowed yet, so there are no locking
		 * considerations. But we should be just as tense as XLogFileInit to
		 * avoid emplacing a bogus file.
		 */
		XLogFileCopy(endLogSegNo, endTLI, endLogSegNo,
					 XLogSegmentOffset(endOfLog, wal_segment_size));
	}
	else
	{
		/*
		 * The switch happened at a segment boundary, so just create the next
		 * segment on the new timeline.
		 */
		bool		use_existent = true;
		int			fd;

		fd = XLogFileInit(startLogSegNo, &use_existent, true);

		if (close(fd) != 0)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not close file \"%s\": %m",
							XLogFileNameP(ThisTimeLineID, startLogSegNo))));
	}

	/*
	 * Let's just make real sure there are not .ready or .done flags posted
	 * for the new segment.
	 */
	XLogFileName(xlogfname, ThisTimeLineID, startLogSegNo, wal_segment_size);
	XLogArchiveCleanup(xlogfname);

	/*
	 * Remove the signal files out of the way, so that we don't accidentally
	 * re-enter archive recovery mode in a subsequent crash.
	 */
	if (standby_signal_file_found)
		durable_unlink(STANDBY_SIGNAL_FILE, FATAL);

	if (recovery_signal_file_found)
		durable_unlink(RECOVERY_SIGNAL_FILE, FATAL);

	ereport(LOG,
			(errmsg("archive recovery complete")));
}