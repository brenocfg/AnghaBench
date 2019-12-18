#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;

/* Variables and functions */
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int /*<<< orphan*/  XLOG_MARK_UNIMPORTANT ; 
 int /*<<< orphan*/  XLOG_SWITCH ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogSetRecordFlags (int /*<<< orphan*/ ) ; 

XLogRecPtr
RequestXLogSwitch(bool mark_unimportant)
{
	XLogRecPtr	RecPtr;

	/* XLOG SWITCH has no data */
	XLogBeginInsert();

	if (mark_unimportant)
		XLogSetRecordFlags(XLOG_MARK_UNIMPORTANT);
	RecPtr = XLogInsert(RM_XLOG_ID, XLOG_SWITCH);

	return RecPtr;
}