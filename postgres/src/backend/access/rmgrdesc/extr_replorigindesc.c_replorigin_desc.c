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
struct TYPE_3__ {int remote_lsn; int /*<<< orphan*/  force; int /*<<< orphan*/  node_id; } ;
typedef  TYPE_1__ xl_replorigin_set ;
struct TYPE_4__ {int /*<<< orphan*/  node_id; } ;
typedef  TYPE_2__ xl_replorigin_drop ;
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
#define  XLOG_REPLORIGIN_DROP 129 
#define  XLOG_REPLORIGIN_SET 128 
 int XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
replorigin_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_REPLORIGIN_SET:
			{
				xl_replorigin_set *xlrec;

				xlrec = (xl_replorigin_set *) rec;

				appendStringInfo(buf, "set %u; lsn %X/%X; force: %d",
								 xlrec->node_id,
								 (uint32) (xlrec->remote_lsn >> 32),
								 (uint32) xlrec->remote_lsn,
								 xlrec->force);
				break;
			}
		case XLOG_REPLORIGIN_DROP:
			{
				xl_replorigin_drop *xlrec;

				xlrec = (xl_replorigin_drop *) rec;

				appendStringInfo(buf, "drop %u", xlrec->node_id);
				break;
			}
	}
}