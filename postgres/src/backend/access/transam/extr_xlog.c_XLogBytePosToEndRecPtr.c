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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;

/* Variables and functions */
 int SizeOfXLogLongPHD ; 
 int SizeOfXLogShortPHD ; 
 int UsableBytesInPage ; 
 int UsableBytesInSegment ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLogSegNoOffsetToRecPtr (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wal_segment_size ; 

__attribute__((used)) static XLogRecPtr
XLogBytePosToEndRecPtr(uint64 bytepos)
{
	uint64		fullsegs;
	uint64		fullpages;
	uint64		bytesleft;
	uint32		seg_offset;
	XLogRecPtr	result;

	fullsegs = bytepos / UsableBytesInSegment;
	bytesleft = bytepos % UsableBytesInSegment;

	if (bytesleft < XLOG_BLCKSZ - SizeOfXLogLongPHD)
	{
		/* fits on first page of segment */
		if (bytesleft == 0)
			seg_offset = 0;
		else
			seg_offset = bytesleft + SizeOfXLogLongPHD;
	}
	else
	{
		/* account for the first page on segment with long header */
		seg_offset = XLOG_BLCKSZ;
		bytesleft -= XLOG_BLCKSZ - SizeOfXLogLongPHD;

		fullpages = bytesleft / UsableBytesInPage;
		bytesleft = bytesleft % UsableBytesInPage;

		if (bytesleft == 0)
			seg_offset += fullpages * XLOG_BLCKSZ + bytesleft;
		else
			seg_offset += fullpages * XLOG_BLCKSZ + bytesleft + SizeOfXLogShortPHD;
	}

	XLogSegNoOffsetToRecPtr(fullsegs, seg_offset, wal_segment_size, result);

	return result;
}