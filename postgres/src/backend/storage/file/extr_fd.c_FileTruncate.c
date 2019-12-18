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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ fileSize; int fdstate; int /*<<< orphan*/  fd; int /*<<< orphan*/  fileName; } ;
typedef  size_t File ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int FD_TEMP_FILE_LIMIT ; 
 int FileAccess (size_t) ; 
 int FileIsValid (size_t) ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_1__* VfdCache ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temporary_files_size ; 

int
FileTruncate(File file, off_t offset, uint32 wait_event_info)
{
	int			returnCode;

	Assert(FileIsValid(file));

	DO_DB(elog(LOG, "FileTruncate %d (%s)",
			   file, VfdCache[file].fileName));

	returnCode = FileAccess(file);
	if (returnCode < 0)
		return returnCode;

	pgstat_report_wait_start(wait_event_info);
	returnCode = ftruncate(VfdCache[file].fd, offset);
	pgstat_report_wait_end();

	if (returnCode == 0 && VfdCache[file].fileSize > offset)
	{
		/* adjust our state for truncation of a temp file */
		Assert(VfdCache[file].fdstate & FD_TEMP_FILE_LIMIT);
		temporary_files_size -= VfdCache[file].fileSize - offset;
		VfdCache[file].fileSize = offset;
	}

	return returnCode;
}