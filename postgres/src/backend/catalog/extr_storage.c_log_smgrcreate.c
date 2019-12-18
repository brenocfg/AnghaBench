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
typedef  int /*<<< orphan*/  xlrec ;
struct TYPE_2__ {int /*<<< orphan*/  forkNum; int /*<<< orphan*/  rnode; } ;
typedef  TYPE_1__ xl_smgr_create ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  RM_SMGR_ID ; 
 int XLOG_SMGR_CREATE ; 
 int XLR_SPECIAL_REL_UPDATE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 

void
log_smgrcreate(const RelFileNode *rnode, ForkNumber forkNum)
{
	xl_smgr_create xlrec;

	/*
	 * Make an XLOG entry reporting the file creation.
	 */
	xlrec.rnode = *rnode;
	xlrec.forkNum = forkNum;

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, sizeof(xlrec));
	XLogInsert(RM_SMGR_ID, XLOG_SMGR_CREATE | XLR_SPECIAL_REL_UPDATE);
}