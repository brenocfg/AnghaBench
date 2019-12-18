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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsPartialXLogFileName (scalar_t__) ; 
 int /*<<< orphan*/  IsXLogFileName (scalar_t__) ; 
 int MAXFNAMELEN ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveXlogFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateLastRemovedPtr (scalar_t__) ; 
 int /*<<< orphan*/  XLOGDIR ; 
 scalar_t__ XLogArchiveCheckDone (scalar_t__) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
RemoveOldXlogFiles(XLogSegNo segno, XLogRecPtr RedoRecPtr, XLogRecPtr endptr)
{
	DIR		   *xldir;
	struct dirent *xlde;
	char		lastoff[MAXFNAMELEN];

	/*
	 * Construct a filename of the last segment to be kept. The timeline ID
	 * doesn't matter, we ignore that in the comparison. (During recovery,
	 * ThisTimeLineID isn't set, so we can't use that.)
	 */
	XLogFileName(lastoff, 0, segno, wal_segment_size);

	elog(DEBUG2, "attempting to remove WAL segments older than log file %s",
		 lastoff);

	xldir = AllocateDir(XLOGDIR);

	while ((xlde = ReadDir(xldir, XLOGDIR)) != NULL)
	{
		/* Ignore files that are not XLOG segments */
		if (!IsXLogFileName(xlde->d_name) &&
			!IsPartialXLogFileName(xlde->d_name))
			continue;

		/*
		 * We ignore the timeline part of the XLOG segment identifiers in
		 * deciding whether a segment is still needed.  This ensures that we
		 * won't prematurely remove a segment from a parent timeline. We could
		 * probably be a little more proactive about removing segments of
		 * non-parent timelines, but that would be a whole lot more
		 * complicated.
		 *
		 * We use the alphanumeric sorting property of the filenames to decide
		 * which ones are earlier than the lastoff segment.
		 */
		if (strcmp(xlde->d_name + 8, lastoff + 8) <= 0)
		{
			if (XLogArchiveCheckDone(xlde->d_name))
			{
				/* Update the last removed location in shared memory first */
				UpdateLastRemovedPtr(xlde->d_name);

				RemoveXlogFile(xlde->d_name, RedoRecPtr, endptr);
			}
		}
	}

	FreeDir(xldir);
}