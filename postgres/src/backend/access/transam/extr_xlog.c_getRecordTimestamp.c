#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xact_time; } ;
typedef  TYPE_1__ xl_xact_commit ;
struct TYPE_5__ {int /*<<< orphan*/  xact_time; } ;
typedef  TYPE_2__ xl_xact_abort ;
struct TYPE_6__ {int /*<<< orphan*/  rp_time; } ;
typedef  TYPE_3__ xl_restore_point ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 scalar_t__ RM_XACT_ID ; 
 scalar_t__ RM_XLOG_ID ; 
 scalar_t__ XLOG_RESTORE_POINT ; 
 scalar_t__ XLOG_XACT_ABORT ; 
 scalar_t__ XLOG_XACT_ABORT_PREPARED ; 
 scalar_t__ XLOG_XACT_COMMIT ; 
 scalar_t__ XLOG_XACT_COMMIT_PREPARED ; 
 scalar_t__ XLOG_XACT_OPMASK ; 
 scalar_t__ XLR_INFO_MASK ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetRmid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
getRecordTimestamp(XLogReaderState *record, TimestampTz *recordXtime)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;
	uint8		xact_info = info & XLOG_XACT_OPMASK;
	uint8		rmid = XLogRecGetRmid(record);

	if (rmid == RM_XLOG_ID && info == XLOG_RESTORE_POINT)
	{
		*recordXtime = ((xl_restore_point *) XLogRecGetData(record))->rp_time;
		return true;
	}
	if (rmid == RM_XACT_ID && (xact_info == XLOG_XACT_COMMIT ||
							   xact_info == XLOG_XACT_COMMIT_PREPARED))
	{
		*recordXtime = ((xl_xact_commit *) XLogRecGetData(record))->xact_time;
		return true;
	}
	if (rmid == RM_XACT_ID && (xact_info == XLOG_XACT_ABORT ||
							   xact_info == XLOG_XACT_ABORT_PREPARED))
	{
		*recordXtime = ((xl_xact_abort *) XLogRecGetData(record))->xact_time;
		return true;
	}
	return false;
}