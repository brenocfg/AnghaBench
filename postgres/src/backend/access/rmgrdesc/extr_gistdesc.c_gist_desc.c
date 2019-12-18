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
typedef  int /*<<< orphan*/  gistxlogPageUpdate ;
typedef  int /*<<< orphan*/  gistxlogPageSplit ;
typedef  int /*<<< orphan*/  gistxlogPageReuse ;
typedef  int /*<<< orphan*/  gistxlogPageDelete ;
typedef  int /*<<< orphan*/  gistxlogDelete ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
#define  XLOG_GIST_DELETE 132 
#define  XLOG_GIST_PAGE_DELETE 131 
#define  XLOG_GIST_PAGE_REUSE 130 
#define  XLOG_GIST_PAGE_SPLIT 129 
#define  XLOG_GIST_PAGE_UPDATE 128 
 int XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_gistxlogDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_gistxlogPageDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_gistxlogPageReuse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_gistxlogPageSplit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_gistxlogPageUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
gist_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_GIST_PAGE_UPDATE:
			out_gistxlogPageUpdate(buf, (gistxlogPageUpdate *) rec);
			break;
		case XLOG_GIST_PAGE_REUSE:
			out_gistxlogPageReuse(buf, (gistxlogPageReuse *) rec);
			break;
		case XLOG_GIST_DELETE:
			out_gistxlogDelete(buf, (gistxlogDelete *) rec);
			break;
		case XLOG_GIST_PAGE_SPLIT:
			out_gistxlogPageSplit(buf, (gistxlogPageSplit *) rec);
			break;
		case XLOG_GIST_PAGE_DELETE:
			out_gistxlogPageDelete(buf, (gistxlogPageDelete *) rec);
			break;
	}
}