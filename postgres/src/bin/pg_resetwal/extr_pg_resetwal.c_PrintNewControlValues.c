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
struct TYPE_3__ {int nextMulti; int oldestMulti; int oldestMultiDB; int nextMultiOffset; int nextOid; int oldestXid; int oldestXidDB; int oldestCommitTsXid; int newestCommitTsXid; int /*<<< orphan*/  nextFullXid; int /*<<< orphan*/  ThisTimeLineID; } ;
struct TYPE_4__ {int xlog_seg_size; TYPE_1__ checkPointCopy; } ;

/* Variables and functions */
 TYPE_2__ ControlFile ; 
 int EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  WalSegSz ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  newXlogSegNo ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ set_mxid ; 
 int set_mxoff ; 
 scalar_t__ set_newest_commit_ts_xid ; 
 scalar_t__ set_oid ; 
 scalar_t__ set_oldest_commit_ts_xid ; 
 scalar_t__ set_wal_segsize ; 
 scalar_t__ set_xid ; 
 int set_xid_epoch ; 

__attribute__((used)) static void
PrintNewControlValues(void)
{
	char		fname[MAXFNAMELEN];

	/* This will be always printed in order to keep format same. */
	printf(_("\n\nValues to be changed:\n\n"));

	XLogFileName(fname, ControlFile.checkPointCopy.ThisTimeLineID,
				 newXlogSegNo, WalSegSz);
	printf(_("First log segment after reset:        %s\n"), fname);

	if (set_mxid != 0)
	{
		printf(_("NextMultiXactId:                      %u\n"),
			   ControlFile.checkPointCopy.nextMulti);
		printf(_("OldestMultiXid:                       %u\n"),
			   ControlFile.checkPointCopy.oldestMulti);
		printf(_("OldestMulti's DB:                     %u\n"),
			   ControlFile.checkPointCopy.oldestMultiDB);
	}

	if (set_mxoff != -1)
	{
		printf(_("NextMultiOffset:                      %u\n"),
			   ControlFile.checkPointCopy.nextMultiOffset);
	}

	if (set_oid != 0)
	{
		printf(_("NextOID:                              %u\n"),
			   ControlFile.checkPointCopy.nextOid);
	}

	if (set_xid != 0)
	{
		printf(_("NextXID:                              %u\n"),
			   XidFromFullTransactionId(ControlFile.checkPointCopy.nextFullXid));
		printf(_("OldestXID:                            %u\n"),
			   ControlFile.checkPointCopy.oldestXid);
		printf(_("OldestXID's DB:                       %u\n"),
			   ControlFile.checkPointCopy.oldestXidDB);
	}

	if (set_xid_epoch != -1)
	{
		printf(_("NextXID epoch:                        %u\n"),
			   EpochFromFullTransactionId(ControlFile.checkPointCopy.nextFullXid));
	}

	if (set_oldest_commit_ts_xid != 0)
	{
		printf(_("oldestCommitTsXid:                    %u\n"),
			   ControlFile.checkPointCopy.oldestCommitTsXid);
	}
	if (set_newest_commit_ts_xid != 0)
	{
		printf(_("newestCommitTsXid:                    %u\n"),
			   ControlFile.checkPointCopy.newestCommitTsXid);
	}

	if (set_wal_segsize != 0)
	{
		printf(_("Bytes per WAL segment:                %u\n"),
			   ControlFile.xlog_seg_size);
	}
}