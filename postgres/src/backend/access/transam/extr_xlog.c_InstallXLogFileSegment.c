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
struct stat {int dummy; } ;
typedef  scalar_t__ XLogSegNo ;

/* Variables and functions */
 int /*<<< orphan*/  ControlFileLock ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  XLogFilePath (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ durable_link_or_rename (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  durable_unlink (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static bool
InstallXLogFileSegment(XLogSegNo *segno, char *tmppath,
					   bool find_free, XLogSegNo max_segno,
					   bool use_lock)
{
	char		path[MAXPGPATH];
	struct stat stat_buf;

	XLogFilePath(path, ThisTimeLineID, *segno, wal_segment_size);

	/*
	 * We want to be sure that only one process does this at a time.
	 */
	if (use_lock)
		LWLockAcquire(ControlFileLock, LW_EXCLUSIVE);

	if (!find_free)
	{
		/* Force installation: get rid of any pre-existing segment file */
		durable_unlink(path, DEBUG1);
	}
	else
	{
		/* Find a free slot to put it in */
		while (stat(path, &stat_buf) == 0)
		{
			if ((*segno) >= max_segno)
			{
				/* Failed to find a free slot within specified range */
				if (use_lock)
					LWLockRelease(ControlFileLock);
				return false;
			}
			(*segno)++;
			XLogFilePath(path, ThisTimeLineID, *segno, wal_segment_size);
		}
	}

	/*
	 * Perform the rename using link if available, paranoidly trying to avoid
	 * overwriting an existing file (there shouldn't be one).
	 */
	if (durable_link_or_rename(tmppath, path, LOG) != 0)
	{
		if (use_lock)
			LWLockRelease(ControlFileLock);
		/* durable_link_or_rename already emitted log message */
		return false;
	}

	if (use_lock)
		LWLockRelease(ControlFileLock);

	return true;
}