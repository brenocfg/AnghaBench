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
struct TYPE_2__ {int pageno; int /*<<< orphan*/  oldestXid; } ;
typedef  TYPE_1__ xl_commit_ts_truncate ;
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_TS_TRUNCATE ; 
 int /*<<< orphan*/  RM_COMMIT_TS_ID ; 
 int /*<<< orphan*/  SizeOfCommitTsTruncate ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
WriteTruncateXlogRec(int pageno, TransactionId oldestXid)
{
	xl_commit_ts_truncate xlrec;

	xlrec.pageno = pageno;
	xlrec.oldestXid = oldestXid;

	XLogBeginInsert();
	XLogRegisterData((char *) (&xlrec), SizeOfCommitTsTruncate);
	(void) XLogInsert(RM_COMMIT_TS_ID, COMMIT_TS_TRUNCATE);
}