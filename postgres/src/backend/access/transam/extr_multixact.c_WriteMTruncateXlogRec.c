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
struct TYPE_2__ {void* endTruncMemb; void* startTruncMemb; void* endTruncOff; void* startTruncOff; int /*<<< orphan*/  oldestMultiDB; } ;
typedef  TYPE_1__ xl_multixact_truncate ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  Oid ;
typedef  void* MultiXactOffset ;
typedef  void* MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  RM_MULTIXACT_ID ; 
 int /*<<< orphan*/  SizeOfMultiXactTruncate ; 
 int /*<<< orphan*/  XLOG_MULTIXACT_TRUNCATE_ID ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
WriteMTruncateXlogRec(Oid oldestMultiDB,
					  MultiXactId startTruncOff, MultiXactId endTruncOff,
					  MultiXactOffset startTruncMemb, MultiXactOffset endTruncMemb)
{
	XLogRecPtr	recptr;
	xl_multixact_truncate xlrec;

	xlrec.oldestMultiDB = oldestMultiDB;

	xlrec.startTruncOff = startTruncOff;
	xlrec.endTruncOff = endTruncOff;

	xlrec.startTruncMemb = startTruncMemb;
	xlrec.endTruncMemb = endTruncMemb;

	XLogBeginInsert();
	XLogRegisterData((char *) (&xlrec), SizeOfMultiXactTruncate);
	recptr = XLogInsert(RM_MULTIXACT_ID, XLOG_MULTIXACT_TRUNCATE_ID);
	XLogFlush(recptr);
}