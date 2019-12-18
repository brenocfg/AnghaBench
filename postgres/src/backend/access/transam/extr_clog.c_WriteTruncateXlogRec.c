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
struct TYPE_2__ {int pageno; int /*<<< orphan*/  oldestXactDb; int /*<<< orphan*/  oldestXact; } ;
typedef  TYPE_1__ xl_clog_truncate ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CLOG_TRUNCATE ; 
 int /*<<< orphan*/  RM_CLOG_ID ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 

__attribute__((used)) static void
WriteTruncateXlogRec(int pageno, TransactionId oldestXact, Oid oldestXactDb)
{
	XLogRecPtr	recptr;
	xl_clog_truncate xlrec;

	xlrec.pageno = pageno;
	xlrec.oldestXact = oldestXact;
	xlrec.oldestXactDb = oldestXactDb;

	XLogBeginInsert();
	XLogRegisterData((char *) (&xlrec), sizeof(xl_clog_truncate));
	recptr = XLogInsert(RM_CLOG_ID, CLOG_TRUNCATE);
	XLogFlush(recptr);
}