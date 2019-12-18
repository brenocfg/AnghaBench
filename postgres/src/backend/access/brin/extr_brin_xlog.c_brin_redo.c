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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC ; 
#define  XLOG_BRIN_CREATE_INDEX 133 
#define  XLOG_BRIN_DESUMMARIZE 132 
#define  XLOG_BRIN_INSERT 131 
 int XLOG_BRIN_OPMASK ; 
#define  XLOG_BRIN_REVMAP_EXTEND 130 
#define  XLOG_BRIN_SAMEPAGE_UPDATE 129 
#define  XLOG_BRIN_UPDATE 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_createidx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_desummarize_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_revmap_extend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_samepage_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_xlog_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

void
brin_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info & XLOG_BRIN_OPMASK)
	{
		case XLOG_BRIN_CREATE_INDEX:
			brin_xlog_createidx(record);
			break;
		case XLOG_BRIN_INSERT:
			brin_xlog_insert(record);
			break;
		case XLOG_BRIN_UPDATE:
			brin_xlog_update(record);
			break;
		case XLOG_BRIN_SAMEPAGE_UPDATE:
			brin_xlog_samepage_update(record);
			break;
		case XLOG_BRIN_REVMAP_EXTEND:
			brin_xlog_revmap_extend(record);
			break;
		case XLOG_BRIN_DESUMMARIZE:
			brin_xlog_desummarize_page(record);
			break;
		default:
			elog(PANIC, "brin_redo: unknown op code %u", info);
	}
}