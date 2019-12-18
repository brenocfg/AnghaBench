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
typedef  scalar_t__ XLogSegNo ;
struct TYPE_2__ {scalar_t__ lastRemovedSegNo; int /*<<< orphan*/  info_lck; } ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* XLogCtl ; 
 int /*<<< orphan*/  XLogFromFileName (char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
UpdateLastRemovedPtr(char *filename)
{
	uint32		tli;
	XLogSegNo	segno;

	XLogFromFileName(filename, &tli, &segno, wal_segment_size);

	SpinLockAcquire(&XLogCtl->info_lck);
	if (segno > XLogCtl->lastRemovedSegNo)
		XLogCtl->lastRemovedSegNo = segno;
	SpinLockRelease(&XLogCtl->info_lck);
}