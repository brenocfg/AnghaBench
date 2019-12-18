#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  int XLogRecPtr ;
typedef  int TransactionId ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPGPATH ; 
 TYPE_2__* MyReplicationSlot ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogSegNoOffsetToRecPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,int,int) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
ReorderBufferSerializedPath(char *path, ReplicationSlot *slot, TransactionId xid,
							XLogSegNo segno)
{
	XLogRecPtr	recptr;

	XLogSegNoOffsetToRecPtr(segno, 0, wal_segment_size, recptr);

	snprintf(path, MAXPGPATH, "pg_replslot/%s/xid-%u-lsn-%X-%X.spill",
			 NameStr(MyReplicationSlot->data.name),
			 xid,
			 (uint32) (recptr >> 32), (uint32) recptr);
}