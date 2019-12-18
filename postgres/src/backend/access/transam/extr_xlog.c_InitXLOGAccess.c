#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ forcePageWrites; scalar_t__ fullPageWrites; } ;
typedef  TYPE_1__ XLogCtlInsert ;
struct TYPE_6__ {int /*<<< orphan*/  xlog_seg_size; } ;
struct TYPE_5__ {scalar_t__ ThisTimeLineID; TYPE_1__ Insert; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__* ControlFile ; 
 int /*<<< orphan*/  GetRedoRecPtr () ; 
 int /*<<< orphan*/  InitXLogInsert () ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 scalar_t__ ThisTimeLineID ; 
 TYPE_2__* XLogCtl ; 
 int doPageWrites ; 
 int /*<<< orphan*/  wal_segment_size ; 

void
InitXLOGAccess(void)
{
	XLogCtlInsert *Insert = &XLogCtl->Insert;

	/* ThisTimeLineID doesn't change so we need no lock to copy it */
	ThisTimeLineID = XLogCtl->ThisTimeLineID;
	Assert(ThisTimeLineID != 0 || IsBootstrapProcessingMode());

	/* set wal_segment_size */
	wal_segment_size = ControlFile->xlog_seg_size;

	/* Use GetRedoRecPtr to copy the RedoRecPtr safely */
	(void) GetRedoRecPtr();
	/* Also update our copy of doPageWrites. */
	doPageWrites = (Insert->fullPageWrites || Insert->forcePageWrites);

	/* Also initialize the working areas for constructing WAL records */
	InitXLogInsert();
}