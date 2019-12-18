#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_3__ {scalar_t__ xl_tot_len; scalar_t__ xl_rmid; int xl_prev; } ;
typedef  TYPE_1__ XLogRecord ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 scalar_t__ RM_MAX_ID ; 
 scalar_t__ SizeOfXLogRecord ; 
 int /*<<< orphan*/  report_invalid_record (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static bool
ValidXLogRecordHeader(XLogReaderState *state, XLogRecPtr RecPtr,
					  XLogRecPtr PrevRecPtr, XLogRecord *record,
					  bool randAccess)
{
	if (record->xl_tot_len < SizeOfXLogRecord)
	{
		report_invalid_record(state,
							  "invalid record length at %X/%X: wanted %u, got %u",
							  (uint32) (RecPtr >> 32), (uint32) RecPtr,
							  (uint32) SizeOfXLogRecord, record->xl_tot_len);
		return false;
	}
	if (record->xl_rmid > RM_MAX_ID)
	{
		report_invalid_record(state,
							  "invalid resource manager ID %u at %X/%X",
							  record->xl_rmid, (uint32) (RecPtr >> 32),
							  (uint32) RecPtr);
		return false;
	}
	if (randAccess)
	{
		/*
		 * We can't exactly verify the prev-link, but surely it should be less
		 * than the record's own address.
		 */
		if (!(record->xl_prev < RecPtr))
		{
			report_invalid_record(state,
								  "record with incorrect prev-link %X/%X at %X/%X",
								  (uint32) (record->xl_prev >> 32),
								  (uint32) record->xl_prev,
								  (uint32) (RecPtr >> 32), (uint32) RecPtr);
			return false;
		}
	}
	else
	{
		/*
		 * Record's prev-link should exactly match our previous location. This
		 * check guards against torn WAL pages where a stale but valid-looking
		 * WAL record starts on a sector boundary.
		 */
		if (record->xl_prev != PrevRecPtr)
		{
			report_invalid_record(state,
								  "record with incorrect prev-link %X/%X at %X/%X",
								  (uint32) (record->xl_prev >> 32),
								  (uint32) record->xl_prev,
								  (uint32) (RecPtr >> 32), (uint32) RecPtr);
			return false;
		}
	}

	return true;
}