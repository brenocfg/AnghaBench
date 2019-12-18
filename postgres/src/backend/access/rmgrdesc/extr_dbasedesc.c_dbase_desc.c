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
struct TYPE_3__ {int /*<<< orphan*/  db_id; int /*<<< orphan*/  tablespace_id; } ;
typedef  TYPE_1__ xl_dbase_drop_rec ;
struct TYPE_4__ {int /*<<< orphan*/  db_id; int /*<<< orphan*/  tablespace_id; int /*<<< orphan*/  src_db_id; int /*<<< orphan*/  src_tablespace_id; } ;
typedef  TYPE_2__ xl_dbase_create_rec ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 scalar_t__ XLOG_DBASE_CREATE ; 
 scalar_t__ XLOG_DBASE_DROP ; 
 scalar_t__ XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

void
dbase_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	if (info == XLOG_DBASE_CREATE)
	{
		xl_dbase_create_rec *xlrec = (xl_dbase_create_rec *) rec;

		appendStringInfo(buf, "copy dir %u/%u to %u/%u",
						 xlrec->src_tablespace_id, xlrec->src_db_id,
						 xlrec->tablespace_id, xlrec->db_id);
	}
	else if (info == XLOG_DBASE_DROP)
	{
		xl_dbase_drop_rec *xlrec = (xl_dbase_drop_rec *) rec;

		appendStringInfo(buf, "dir %u/%u",
						 xlrec->tablespace_id, xlrec->db_id);
	}
}