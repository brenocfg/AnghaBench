#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  new_xmax; int /*<<< orphan*/  new_offnum; int /*<<< orphan*/  old_infobits_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  old_xmax; int /*<<< orphan*/  old_offnum; } ;
typedef  TYPE_1__ xl_heap_update ;
struct TYPE_9__ {int flags; int nrelids; int* relids; } ;
typedef  TYPE_2__ xl_heap_truncate ;
struct TYPE_10__ {int /*<<< orphan*/  infobits_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  locking_xid; int /*<<< orphan*/  offnum; } ;
typedef  TYPE_3__ xl_heap_lock ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  offnum; } ;
typedef  TYPE_4__ xl_heap_insert ;
struct TYPE_12__ {int offnum; } ;
typedef  TYPE_5__ xl_heap_inplace ;
struct TYPE_13__ {int /*<<< orphan*/  infobits_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  offnum; } ;
typedef  TYPE_6__ xl_heap_delete ;
struct TYPE_14__ {int offnum; } ;
typedef  TYPE_7__ xl_heap_confirm ;
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int XLH_TRUNCATE_CASCADE ; 
 int XLH_TRUNCATE_RESTART_SEQS ; 
 int XLOG_HEAP_CONFIRM ; 
 int XLOG_HEAP_DELETE ; 
 int XLOG_HEAP_HOT_UPDATE ; 
 int XLOG_HEAP_INPLACE ; 
 int XLOG_HEAP_INSERT ; 
 int XLOG_HEAP_LOCK ; 
 int XLOG_HEAP_OPMASK ; 
 int XLOG_HEAP_TRUNCATE ; 
 int XLOG_HEAP_UPDATE ; 
 int XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  out_infobits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
heap_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	info &= XLOG_HEAP_OPMASK;
	if (info == XLOG_HEAP_INSERT)
	{
		xl_heap_insert *xlrec = (xl_heap_insert *) rec;

		appendStringInfo(buf, "off %u flags 0x%02X", xlrec->offnum,
						 xlrec->flags);
	}
	else if (info == XLOG_HEAP_DELETE)
	{
		xl_heap_delete *xlrec = (xl_heap_delete *) rec;

		appendStringInfo(buf, "off %u flags 0x%02X ",
						 xlrec->offnum,
						 xlrec->flags);
		out_infobits(buf, xlrec->infobits_set);
	}
	else if (info == XLOG_HEAP_UPDATE)
	{
		xl_heap_update *xlrec = (xl_heap_update *) rec;

		appendStringInfo(buf, "off %u xmax %u flags 0x%02X ",
						 xlrec->old_offnum,
						 xlrec->old_xmax,
						 xlrec->flags);
		out_infobits(buf, xlrec->old_infobits_set);
		appendStringInfo(buf, "; new off %u xmax %u",
						 xlrec->new_offnum,
						 xlrec->new_xmax);
	}
	else if (info == XLOG_HEAP_HOT_UPDATE)
	{
		xl_heap_update *xlrec = (xl_heap_update *) rec;

		appendStringInfo(buf, "off %u xmax %u flags 0x%02X ",
						 xlrec->old_offnum,
						 xlrec->old_xmax,
						 xlrec->flags);
		out_infobits(buf, xlrec->old_infobits_set);
		appendStringInfo(buf, "; new off %u xmax %u",
						 xlrec->new_offnum,
						 xlrec->new_xmax);
	}
	else if (info == XLOG_HEAP_TRUNCATE)
	{
		xl_heap_truncate *xlrec = (xl_heap_truncate *) rec;
		int			i;

		if (xlrec->flags & XLH_TRUNCATE_CASCADE)
			appendStringInfoString(buf, "cascade ");
		if (xlrec->flags & XLH_TRUNCATE_RESTART_SEQS)
			appendStringInfoString(buf, "restart_seqs ");
		appendStringInfo(buf, "nrelids %u relids", xlrec->nrelids);
		for (i = 0; i < xlrec->nrelids; i++)
			appendStringInfo(buf, " %u", xlrec->relids[i]);
	}
	else if (info == XLOG_HEAP_CONFIRM)
	{
		xl_heap_confirm *xlrec = (xl_heap_confirm *) rec;

		appendStringInfo(buf, "off %u", xlrec->offnum);
	}
	else if (info == XLOG_HEAP_LOCK)
	{
		xl_heap_lock *xlrec = (xl_heap_lock *) rec;

		appendStringInfo(buf, "off %u: xid %u: flags 0x%02X ",
						 xlrec->offnum, xlrec->locking_xid, xlrec->flags);
		out_infobits(buf, xlrec->infobits_set);
	}
	else if (info == XLOG_HEAP_INPLACE)
	{
		xl_heap_inplace *xlrec = (xl_heap_inplace *) rec;

		appendStringInfo(buf, "off %u", xlrec->offnum);
	}
}