#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
struct TYPE_4__ {char* data; int len; struct TYPE_4__* next; } ;
typedef  TYPE_1__ XLogRecData ;
typedef  TYPE_2__* XLogPageHeader ;
struct TYPE_5__ {int xlp_rem_len; int /*<<< orphan*/  xlp_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* GetXLogBuffer (int) ; 
 int INSERT_FREESPACE (int) ; 
 int MAXALIGN64 (int) ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ SizeOfXLogLongPHD ; 
 int SizeOfXLogRecord ; 
 int SizeOfXLogShortPHD ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLP_FIRST_IS_CONTRECORD ; 
 scalar_t__ XLogSegmentOffset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static void
CopyXLogRecordToWAL(int write_len, bool isLogSwitch, XLogRecData *rdata,
					XLogRecPtr StartPos, XLogRecPtr EndPos)
{
	char	   *currpos;
	int			freespace;
	int			written;
	XLogRecPtr	CurrPos;
	XLogPageHeader pagehdr;

	/*
	 * Get a pointer to the right place in the right WAL buffer to start
	 * inserting to.
	 */
	CurrPos = StartPos;
	currpos = GetXLogBuffer(CurrPos);
	freespace = INSERT_FREESPACE(CurrPos);

	/*
	 * there should be enough space for at least the first field (xl_tot_len)
	 * on this page.
	 */
	Assert(freespace >= sizeof(uint32));

	/* Copy record data */
	written = 0;
	while (rdata != NULL)
	{
		char	   *rdata_data = rdata->data;
		int			rdata_len = rdata->len;

		while (rdata_len > freespace)
		{
			/*
			 * Write what fits on this page, and continue on the next page.
			 */
			Assert(CurrPos % XLOG_BLCKSZ >= SizeOfXLogShortPHD || freespace == 0);
			memcpy(currpos, rdata_data, freespace);
			rdata_data += freespace;
			rdata_len -= freespace;
			written += freespace;
			CurrPos += freespace;

			/*
			 * Get pointer to beginning of next page, and set the xlp_rem_len
			 * in the page header. Set XLP_FIRST_IS_CONTRECORD.
			 *
			 * It's safe to set the contrecord flag and xlp_rem_len without a
			 * lock on the page. All the other flags were already set when the
			 * page was initialized, in AdvanceXLInsertBuffer, and we're the
			 * only backend that needs to set the contrecord flag.
			 */
			currpos = GetXLogBuffer(CurrPos);
			pagehdr = (XLogPageHeader) currpos;
			pagehdr->xlp_rem_len = write_len - written;
			pagehdr->xlp_info |= XLP_FIRST_IS_CONTRECORD;

			/* skip over the page header */
			if (XLogSegmentOffset(CurrPos, wal_segment_size) == 0)
			{
				CurrPos += SizeOfXLogLongPHD;
				currpos += SizeOfXLogLongPHD;
			}
			else
			{
				CurrPos += SizeOfXLogShortPHD;
				currpos += SizeOfXLogShortPHD;
			}
			freespace = INSERT_FREESPACE(CurrPos);
		}

		Assert(CurrPos % XLOG_BLCKSZ >= SizeOfXLogShortPHD || rdata_len == 0);
		memcpy(currpos, rdata_data, rdata_len);
		currpos += rdata_len;
		CurrPos += rdata_len;
		freespace -= rdata_len;
		written += rdata_len;

		rdata = rdata->next;
	}
	Assert(written == write_len);

	/*
	 * If this was an xlog-switch, it's not enough to write the switch record,
	 * we also have to consume all the remaining space in the WAL segment.  We
	 * have already reserved that space, but we need to actually fill it.
	 */
	if (isLogSwitch && XLogSegmentOffset(CurrPos, wal_segment_size) != 0)
	{
		/* An xlog-switch record doesn't contain any data besides the header */
		Assert(write_len == SizeOfXLogRecord);

		/* Assert that we did reserve the right amount of space */
		Assert(XLogSegmentOffset(EndPos, wal_segment_size) == 0);

		/* Use up all the remaining space on the current page */
		CurrPos += freespace;

		/*
		 * Cause all remaining pages in the segment to be flushed, leaving the
		 * XLog position where it should be, at the start of the next segment.
		 * We do this one page at a time, to make sure we don't deadlock
		 * against ourselves if wal_buffers < wal_segment_size.
		 */
		while (CurrPos < EndPos)
		{
			/*
			 * The minimal action to flush the page would be to call
			 * WALInsertLockUpdateInsertingAt(CurrPos) followed by
			 * AdvanceXLInsertBuffer(...).  The page would be left initialized
			 * mostly to zeros, except for the page header (always the short
			 * variant, as this is never a segment's first page).
			 *
			 * The large vistas of zeros are good for compressibility, but the
			 * headers interrupting them every XLOG_BLCKSZ (with values that
			 * differ from page to page) are not.  The effect varies with
			 * compression tool, but bzip2 for instance compresses about an
			 * order of magnitude worse if those headers are left in place.
			 *
			 * Rather than complicating AdvanceXLInsertBuffer itself (which is
			 * called in heavily-loaded circumstances as well as this lightly-
			 * loaded one) with variant behavior, we just use GetXLogBuffer
			 * (which itself calls the two methods we need) to get the pointer
			 * and zero most of the page.  Then we just zero the page header.
			 */
			currpos = GetXLogBuffer(CurrPos);
			MemSet(currpos, 0, SizeOfXLogShortPHD);

			CurrPos += XLOG_BLCKSZ;
		}
	}
	else
	{
		/* Align the end position, so that the next record starts aligned */
		CurrPos = MAXALIGN64(CurrPos);
	}

	if (CurrPos != EndPos)
		elog(PANIC, "space reserved for WAL record does not match what was written");
}