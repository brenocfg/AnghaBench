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
struct TYPE_2__ {int /*<<< orphan*/  latestRemovedXid; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ xl_heap_cleanup_info ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  RelFileNode ;

/* Variables and functions */
 int /*<<< orphan*/  RM_HEAP2_ID ; 
 int /*<<< orphan*/  SizeOfHeapCleanupInfo ; 
 int /*<<< orphan*/  XLOG_HEAP2_CLEANUP_INFO ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

XLogRecPtr
log_heap_cleanup_info(RelFileNode rnode, TransactionId latestRemovedXid)
{
	xl_heap_cleanup_info xlrec;
	XLogRecPtr	recptr;

	xlrec.node = rnode;
	xlrec.latestRemovedXid = latestRemovedXid;

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, SizeOfHeapCleanupInfo);

	recptr = XLogInsert(RM_HEAP2_ID, XLOG_HEAP2_CLEANUP_INFO);

	return recptr;
}