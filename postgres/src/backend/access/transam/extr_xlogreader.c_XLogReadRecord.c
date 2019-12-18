#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_20__ {int xl_tot_len; scalar_t__ xl_rmid; int xl_info; } ;
typedef  TYPE_2__ XLogRecord ;
typedef  int XLogRecPtr ;
struct TYPE_19__ {int ws_segsize; } ;
struct TYPE_21__ {char* errormsg_buf; int EndRecPtr; int ReadRecPtr; int currRecPtr; char* readBuf; int readRecordBufSize; char* readRecordBuf; TYPE_1__ segcxt; } ;
typedef  TYPE_3__ XLogReaderState ;
typedef  TYPE_4__* XLogPageHeader ;
struct TYPE_22__ {int xlp_info; int xlp_rem_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DecodeXLogRecord (TYPE_3__*,TYPE_2__*,char**) ; 
 int InvalidXLogRecPtr ; 
 int MAXALIGN (int) ; 
 int Min (int,int) ; 
 scalar_t__ RM_XLOG_ID ; 
 int ReadPageInternal (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ResetDecoder (TYPE_3__*) ; 
 int SizeOfXLogRecord ; 
 int SizeOfXLogShortPHD ; 
 int /*<<< orphan*/  ValidXLogRecord (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ValidXLogRecordHeader (TYPE_3__*,int,int,TYPE_2__*,int) ; 
 int XLOG_BLCKSZ ; 
 int XLOG_SWITCH ; 
 int XLP_FIRST_IS_CONTRECORD ; 
 int XLR_INFO_MASK ; 
 int XLogPageHeaderSize (TYPE_4__*) ; 
 int /*<<< orphan*/  XLogReaderInvalReadState (TYPE_3__*) ; 
 int XLogSegmentOffset (int,int) ; 
 int XRecOffIsValid (int) ; 
 int /*<<< orphan*/  allocate_recordbuf (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  report_invalid_record (TYPE_3__*,char*,int,int,...) ; 

XLogRecord *
XLogReadRecord(XLogReaderState *state, XLogRecPtr RecPtr, char **errormsg)
{
	XLogRecord *record;
	XLogRecPtr	targetPagePtr;
	bool		randAccess;
	uint32		len,
				total_len;
	uint32		targetRecOff;
	uint32		pageHeaderSize;
	bool		gotheader;
	int			readOff;

	/*
	 * randAccess indicates whether to verify the previous-record pointer of
	 * the record we're reading.  We only do this if we're reading
	 * sequentially, which is what we initially assume.
	 */
	randAccess = false;

	/* reset error state */
	*errormsg = NULL;
	state->errormsg_buf[0] = '\0';

	ResetDecoder(state);

	if (RecPtr == InvalidXLogRecPtr)
	{
		/* No explicit start point; read the record after the one we just read */
		RecPtr = state->EndRecPtr;

		if (state->ReadRecPtr == InvalidXLogRecPtr)
			randAccess = true;

		/*
		 * RecPtr is pointing to end+1 of the previous WAL record.  If we're
		 * at a page boundary, no more records can fit on the current page. We
		 * must skip over the page header, but we can't do that until we've
		 * read in the page, since the header size is variable.
		 */
	}
	else
	{
		/*
		 * Caller supplied a position to start at.
		 *
		 * In this case, the passed-in record pointer should already be
		 * pointing to a valid record starting position.
		 */
		Assert(XRecOffIsValid(RecPtr));
		randAccess = true;
	}

	state->currRecPtr = RecPtr;

	targetPagePtr = RecPtr - (RecPtr % XLOG_BLCKSZ);
	targetRecOff = RecPtr % XLOG_BLCKSZ;

	/*
	 * Read the page containing the record into state->readBuf. Request enough
	 * byte to cover the whole record header, or at least the part of it that
	 * fits on the same page.
	 */
	readOff = ReadPageInternal(state,
							   targetPagePtr,
							   Min(targetRecOff + SizeOfXLogRecord, XLOG_BLCKSZ));
	if (readOff < 0)
		goto err;

	/*
	 * ReadPageInternal always returns at least the page header, so we can
	 * examine it now.
	 */
	pageHeaderSize = XLogPageHeaderSize((XLogPageHeader) state->readBuf);
	if (targetRecOff == 0)
	{
		/*
		 * At page start, so skip over page header.
		 */
		RecPtr += pageHeaderSize;
		targetRecOff = pageHeaderSize;
	}
	else if (targetRecOff < pageHeaderSize)
	{
		report_invalid_record(state, "invalid record offset at %X/%X",
							  (uint32) (RecPtr >> 32), (uint32) RecPtr);
		goto err;
	}

	if ((((XLogPageHeader) state->readBuf)->xlp_info & XLP_FIRST_IS_CONTRECORD) &&
		targetRecOff == pageHeaderSize)
	{
		report_invalid_record(state, "contrecord is requested by %X/%X",
							  (uint32) (RecPtr >> 32), (uint32) RecPtr);
		goto err;
	}

	/* ReadPageInternal has verified the page header */
	Assert(pageHeaderSize <= readOff);

	/*
	 * Read the record length.
	 *
	 * NB: Even though we use an XLogRecord pointer here, the whole record
	 * header might not fit on this page. xl_tot_len is the first field of the
	 * struct, so it must be on this page (the records are MAXALIGNed), but we
	 * cannot access any other fields until we've verified that we got the
	 * whole header.
	 */
	record = (XLogRecord *) (state->readBuf + RecPtr % XLOG_BLCKSZ);
	total_len = record->xl_tot_len;

	/*
	 * If the whole record header is on this page, validate it immediately.
	 * Otherwise do just a basic sanity check on xl_tot_len, and validate the
	 * rest of the header after reading it from the next page.  The xl_tot_len
	 * check is necessary here to ensure that we enter the "Need to reassemble
	 * record" code path below; otherwise we might fail to apply
	 * ValidXLogRecordHeader at all.
	 */
	if (targetRecOff <= XLOG_BLCKSZ - SizeOfXLogRecord)
	{
		if (!ValidXLogRecordHeader(state, RecPtr, state->ReadRecPtr, record,
								   randAccess))
			goto err;
		gotheader = true;
	}
	else
	{
		/* XXX: more validation should be done here */
		if (total_len < SizeOfXLogRecord)
		{
			report_invalid_record(state,
								  "invalid record length at %X/%X: wanted %u, got %u",
								  (uint32) (RecPtr >> 32), (uint32) RecPtr,
								  (uint32) SizeOfXLogRecord, total_len);
			goto err;
		}
		gotheader = false;
	}

	len = XLOG_BLCKSZ - RecPtr % XLOG_BLCKSZ;
	if (total_len > len)
	{
		/* Need to reassemble record */
		char	   *contdata;
		XLogPageHeader pageHeader;
		char	   *buffer;
		uint32		gotlen;

		/*
		 * Enlarge readRecordBuf as needed.
		 */
		if (total_len > state->readRecordBufSize &&
			!allocate_recordbuf(state, total_len))
		{
			/* We treat this as a "bogus data" condition */
			report_invalid_record(state, "record length %u at %X/%X too long",
								  total_len,
								  (uint32) (RecPtr >> 32), (uint32) RecPtr);
			goto err;
		}

		/* Copy the first fragment of the record from the first page. */
		memcpy(state->readRecordBuf,
			   state->readBuf + RecPtr % XLOG_BLCKSZ, len);
		buffer = state->readRecordBuf + len;
		gotlen = len;

		do
		{
			/* Calculate pointer to beginning of next page */
			targetPagePtr += XLOG_BLCKSZ;

			/* Wait for the next page to become available */
			readOff = ReadPageInternal(state, targetPagePtr,
									   Min(total_len - gotlen + SizeOfXLogShortPHD,
										   XLOG_BLCKSZ));

			if (readOff < 0)
				goto err;

			Assert(SizeOfXLogShortPHD <= readOff);

			/* Check that the continuation on next page looks valid */
			pageHeader = (XLogPageHeader) state->readBuf;
			if (!(pageHeader->xlp_info & XLP_FIRST_IS_CONTRECORD))
			{
				report_invalid_record(state,
									  "there is no contrecord flag at %X/%X",
									  (uint32) (RecPtr >> 32), (uint32) RecPtr);
				goto err;
			}

			/*
			 * Cross-check that xlp_rem_len agrees with how much of the record
			 * we expect there to be left.
			 */
			if (pageHeader->xlp_rem_len == 0 ||
				total_len != (pageHeader->xlp_rem_len + gotlen))
			{
				report_invalid_record(state,
									  "invalid contrecord length %u at %X/%X",
									  pageHeader->xlp_rem_len,
									  (uint32) (RecPtr >> 32), (uint32) RecPtr);
				goto err;
			}

			/* Append the continuation from this page to the buffer */
			pageHeaderSize = XLogPageHeaderSize(pageHeader);

			if (readOff < pageHeaderSize)
				readOff = ReadPageInternal(state, targetPagePtr,
										   pageHeaderSize);

			Assert(pageHeaderSize <= readOff);

			contdata = (char *) state->readBuf + pageHeaderSize;
			len = XLOG_BLCKSZ - pageHeaderSize;
			if (pageHeader->xlp_rem_len < len)
				len = pageHeader->xlp_rem_len;

			if (readOff < pageHeaderSize + len)
				readOff = ReadPageInternal(state, targetPagePtr,
										   pageHeaderSize + len);

			memcpy(buffer, (char *) contdata, len);
			buffer += len;
			gotlen += len;

			/* If we just reassembled the record header, validate it. */
			if (!gotheader)
			{
				record = (XLogRecord *) state->readRecordBuf;
				if (!ValidXLogRecordHeader(state, RecPtr, state->ReadRecPtr,
										   record, randAccess))
					goto err;
				gotheader = true;
			}
		} while (gotlen < total_len);

		Assert(gotheader);

		record = (XLogRecord *) state->readRecordBuf;
		if (!ValidXLogRecord(state, record, RecPtr))
			goto err;

		pageHeaderSize = XLogPageHeaderSize((XLogPageHeader) state->readBuf);
		state->ReadRecPtr = RecPtr;
		state->EndRecPtr = targetPagePtr + pageHeaderSize
			+ MAXALIGN(pageHeader->xlp_rem_len);
	}
	else
	{
		/* Wait for the record data to become available */
		readOff = ReadPageInternal(state, targetPagePtr,
								   Min(targetRecOff + total_len, XLOG_BLCKSZ));
		if (readOff < 0)
			goto err;

		/* Record does not cross a page boundary */
		if (!ValidXLogRecord(state, record, RecPtr))
			goto err;

		state->EndRecPtr = RecPtr + MAXALIGN(total_len);

		state->ReadRecPtr = RecPtr;
	}

	/*
	 * Special processing if it's an XLOG SWITCH record
	 */
	if (record->xl_rmid == RM_XLOG_ID &&
		(record->xl_info & ~XLR_INFO_MASK) == XLOG_SWITCH)
	{
		/* Pretend it extends to end of segment */
		state->EndRecPtr += state->segcxt.ws_segsize - 1;
		state->EndRecPtr -= XLogSegmentOffset(state->EndRecPtr, state->segcxt.ws_segsize);
	}

	if (DecodeXLogRecord(state, record, errormsg))
		return record;
	else
		return NULL;

err:

	/*
	 * Invalidate the read state. We might read from a different source after
	 * failure.
	 */
	XLogReaderInvalReadState(state);

	if (state->errormsg_buf[0] != '\0')
		*errormsg = state->errormsg_buf;

	return NULL;
}