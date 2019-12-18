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
struct dirent {scalar_t__ d_name; } ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TimeLineID ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  IsXLogFileName (scalar_t__) ; 
 int MAXFNAMELEN ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveXlogFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLByteToPrevSeg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOGDIR ; 
 int /*<<< orphan*/  XLogArchiveIsReady (scalar_t__) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
RemoveNonParentXlogFiles(XLogRecPtr switchpoint, TimeLineID newTLI)
{
	DIR		   *xldir;
	struct dirent *xlde;
	char		switchseg[MAXFNAMELEN];
	XLogSegNo	endLogSegNo;

	XLByteToPrevSeg(switchpoint, endLogSegNo, wal_segment_size);

	/*
	 * Construct a filename of the last segment to be kept.
	 */
	XLogFileName(switchseg, newTLI, endLogSegNo, wal_segment_size);

	elog(DEBUG2, "attempting to remove WAL segments newer than log file %s",
		 switchseg);

	xldir = AllocateDir(XLOGDIR);

	while ((xlde = ReadDir(xldir, XLOGDIR)) != NULL)
	{
		/* Ignore files that are not XLOG segments */
		if (!IsXLogFileName(xlde->d_name))
			continue;

		/*
		 * Remove files that are on a timeline older than the new one we're
		 * switching to, but with a segment number >= the first segment on the
		 * new timeline.
		 */
		if (strncmp(xlde->d_name, switchseg, 8) < 0 &&
			strcmp(xlde->d_name + 8, switchseg + 8) > 0)
		{
			/*
			 * If the file has already been marked as .ready, however, don't
			 * remove it yet. It should be OK to remove it - files that are
			 * not part of our timeline history are not required for recovery
			 * - but seems safer to let them be archived and removed later.
			 */
			if (!XLogArchiveIsReady(xlde->d_name))
				RemoveXlogFile(xlde->d_name, InvalidXLogRecPtr, switchpoint);
		}
	}

	FreeDir(xldir);
}