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
typedef  int /*<<< orphan*/  XLogSegNo ;

/* Variables and functions */
 int BasicOpenFile (char*,int) ; 
 int MAXPGPATH ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PANIC ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  XLogFilePath (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int get_sync_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_method ; 
 int /*<<< orphan*/  wal_segment_size ; 

int
XLogFileOpen(XLogSegNo segno)
{
	char		path[MAXPGPATH];
	int			fd;

	XLogFilePath(path, ThisTimeLineID, segno, wal_segment_size);

	fd = BasicOpenFile(path, O_RDWR | PG_BINARY | get_sync_bit(sync_method));
	if (fd < 0)
		ereport(PANIC,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m", path)));

	return fd;
}