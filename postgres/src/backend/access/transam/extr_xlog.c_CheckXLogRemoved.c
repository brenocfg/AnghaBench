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
typedef  scalar_t__ XLogSegNo ;
typedef  int /*<<< orphan*/  TimeLineID ;
struct TYPE_2__ {scalar_t__ lastRemovedSegNo; int /*<<< orphan*/  info_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* XLogCtl ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  wal_segment_size ; 

void
CheckXLogRemoved(XLogSegNo segno, TimeLineID tli)
{
	int			save_errno = errno;
	XLogSegNo	lastRemovedSegNo;

	SpinLockAcquire(&XLogCtl->info_lck);
	lastRemovedSegNo = XLogCtl->lastRemovedSegNo;
	SpinLockRelease(&XLogCtl->info_lck);

	if (segno <= lastRemovedSegNo)
	{
		char		filename[MAXFNAMELEN];

		XLogFileName(filename, tli, segno, wal_segment_size);
		errno = save_errno;
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("requested WAL segment %s has already been removed",
						filename)));
	}
	errno = save_errno;
}