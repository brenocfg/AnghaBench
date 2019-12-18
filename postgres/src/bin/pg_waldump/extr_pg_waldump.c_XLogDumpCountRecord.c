#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
struct TYPE_7__ {TYPE_2__** record_stats; TYPE_1__* rmgr_stats; int /*<<< orphan*/  count; } ;
typedef  TYPE_3__ XLogDumpStats ;
typedef  int /*<<< orphan*/  XLogDumpConfig ;
struct TYPE_6__ {int /*<<< orphan*/  fpi_len; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  fpi_len; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  count; } ;
typedef  size_t RmgrId ;

/* Variables and functions */
 int /*<<< orphan*/  XLogDumpRecordLen (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 size_t XLogRecGetRmid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
XLogDumpCountRecord(XLogDumpConfig *config, XLogDumpStats *stats,
					XLogReaderState *record)
{
	RmgrId		rmid;
	uint8		recid;
	uint32		rec_len;
	uint32		fpi_len;

	stats->count++;

	rmid = XLogRecGetRmid(record);

	XLogDumpRecordLen(record, &rec_len, &fpi_len);

	/* Update per-rmgr statistics */

	stats->rmgr_stats[rmid].count++;
	stats->rmgr_stats[rmid].rec_len += rec_len;
	stats->rmgr_stats[rmid].fpi_len += fpi_len;

	/*
	 * Update per-record statistics, where the record is identified by a
	 * combination of the RmgrId and the four bits of the xl_info field that
	 * are the rmgr's domain (resulting in sixteen possible entries per
	 * RmgrId).
	 */

	recid = XLogRecGetInfo(record) >> 4;

	stats->record_stats[rmid][recid].count++;
	stats->record_stats[rmid][recid].rec_len += rec_len;
	stats->record_stats[rmid][recid].fpi_len += fpi_len;
}