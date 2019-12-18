#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogSegNo ;
struct TYPE_3__ {scalar_t__ first_lsn; scalar_t__ final_lsn; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  MyReplicationSlot ; 
 int /*<<< orphan*/  ReorderBufferSerializedPath (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XLByteToSeg (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ unlink (char*) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
ReorderBufferRestoreCleanup(ReorderBuffer *rb, ReorderBufferTXN *txn)
{
	XLogSegNo	first;
	XLogSegNo	cur;
	XLogSegNo	last;

	Assert(txn->first_lsn != InvalidXLogRecPtr);
	Assert(txn->final_lsn != InvalidXLogRecPtr);

	XLByteToSeg(txn->first_lsn, first, wal_segment_size);
	XLByteToSeg(txn->final_lsn, last, wal_segment_size);

	/* iterate over all possible filenames, and delete them */
	for (cur = first; cur <= last; cur++)
	{
		char		path[MAXPGPATH];

		ReorderBufferSerializedPath(path, MyReplicationSlot, txn->xid, cur);
		if (unlink(path) != 0 && errno != ENOENT)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not remove file \"%s\": %m", path)));
	}
}