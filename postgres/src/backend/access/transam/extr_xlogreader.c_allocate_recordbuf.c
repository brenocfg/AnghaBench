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
typedef  int uint32 ;
struct TYPE_3__ {char* readRecordBuf; int readRecordBufSize; } ;
typedef  TYPE_1__ XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  AllocSizeIsValid (int) ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  MCXT_ALLOC_NO_OOM ; 
 int Max (int,int) ; 
 int XLOG_BLCKSZ ; 
 scalar_t__ palloc_extended (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static bool
allocate_recordbuf(XLogReaderState *state, uint32 reclength)
{
	uint32		newSize = reclength;

	newSize += XLOG_BLCKSZ - (newSize % XLOG_BLCKSZ);
	newSize = Max(newSize, 5 * Max(BLCKSZ, XLOG_BLCKSZ));

#ifndef FRONTEND

	/*
	 * Note that in much unlucky circumstances, the random data read from a
	 * recycled segment can cause this routine to be called with a size
	 * causing a hard failure at allocation.  For a standby, this would cause
	 * the instance to stop suddenly with a hard failure, preventing it to
	 * retry fetching WAL from one of its sources which could allow it to move
	 * on with replay without a manual restart. If the data comes from a past
	 * recycled segment and is still valid, then the allocation may succeed
	 * but record checks are going to fail so this would be short-lived.  If
	 * the allocation fails because of a memory shortage, then this is not a
	 * hard failure either per the guarantee given by MCXT_ALLOC_NO_OOM.
	 */
	if (!AllocSizeIsValid(newSize))
		return false;

#endif

	if (state->readRecordBuf)
		pfree(state->readRecordBuf);
	state->readRecordBuf =
		(char *) palloc_extended(newSize, MCXT_ALLOC_NO_OOM);
	if (state->readRecordBuf == NULL)
	{
		state->readRecordBufSize = 0;
		return false;
	}
	state->readRecordBufSize = newSize;
	return true;
}