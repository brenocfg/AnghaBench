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
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  blkno; int /*<<< orphan*/  rnode; } ;
typedef  TYPE_1__ xl_smgr_truncate ;
struct TYPE_4__ {int /*<<< orphan*/  forkNum; int /*<<< orphan*/  rnode; } ;
typedef  TYPE_2__ xl_smgr_create ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ XLOG_SMGR_CREATE ; 
 scalar_t__ XLOG_SMGR_TRUNCATE ; 
 scalar_t__ XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* relpathperm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
smgr_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	if (info == XLOG_SMGR_CREATE)
	{
		xl_smgr_create *xlrec = (xl_smgr_create *) rec;
		char	   *path = relpathperm(xlrec->rnode, xlrec->forkNum);

		appendStringInfoString(buf, path);
		pfree(path);
	}
	else if (info == XLOG_SMGR_TRUNCATE)
	{
		xl_smgr_truncate *xlrec = (xl_smgr_truncate *) rec;
		char	   *path = relpathperm(xlrec->rnode, MAIN_FORKNUM);

		appendStringInfo(buf, "%s to %u blocks flags %d", path,
						 xlrec->blkno, xlrec->flags);
		pfree(path);
	}
}