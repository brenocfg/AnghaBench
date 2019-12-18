#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_7__ {scalar_t__ ws_tli; } ;
struct TYPE_6__ {int /*<<< orphan*/  ws_segsize; } ;
struct TYPE_8__ {scalar_t__ currTLI; scalar_t__ currTLIValidUntil; TYPE_2__ seg; TYPE_1__ segcxt; } ;
typedef  TYPE_3__ XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ GetFlushRecPtr () ; 
 scalar_t__ GetXLogReplayRecPtr (scalar_t__*) ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 scalar_t__ ThisTimeLineID ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLogRead (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogReadDetermineTimeline (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

int
read_local_xlog_page(XLogReaderState *state, XLogRecPtr targetPagePtr,
					 int reqLen, XLogRecPtr targetRecPtr, char *cur_page)
{
	XLogRecPtr	read_upto,
				loc;
	int			count;

	loc = targetPagePtr + reqLen;

	/* Loop waiting for xlog to be available if necessary */
	while (1)
	{
		/*
		 * Determine the limit of xlog we can currently read to, and what the
		 * most recent timeline is.
		 *
		 * RecoveryInProgress() will update ThisTimeLineID when it first
		 * notices recovery finishes, so we only have to maintain it for the
		 * local process until recovery ends.
		 */
		if (!RecoveryInProgress())
			read_upto = GetFlushRecPtr();
		else
			read_upto = GetXLogReplayRecPtr(&ThisTimeLineID);
		state->seg.ws_tli = ThisTimeLineID;

		/*
		 * Check which timeline to get the record from.
		 *
		 * We have to do it each time through the loop because if we're in
		 * recovery as a cascading standby, the current timeline might've
		 * become historical. We can't rely on RecoveryInProgress() because in
		 * a standby configuration like
		 *
		 * A => B => C
		 *
		 * if we're a logical decoding session on C, and B gets promoted, our
		 * timeline will change while we remain in recovery.
		 *
		 * We can't just keep reading from the old timeline as the last WAL
		 * archive in the timeline will get renamed to .partial by
		 * StartupXLOG().
		 *
		 * If that happens after our caller updated ThisTimeLineID but before
		 * we actually read the xlog page, we might still try to read from the
		 * old (now renamed) segment and fail. There's not much we can do
		 * about this, but it can only happen when we're a leaf of a cascading
		 * standby whose master gets promoted while we're decoding, so a
		 * one-off ERROR isn't too bad.
		 */
		XLogReadDetermineTimeline(state, targetPagePtr, reqLen);

		if (state->currTLI == ThisTimeLineID)
		{

			if (loc <= read_upto)
				break;

			CHECK_FOR_INTERRUPTS();
			pg_usleep(1000L);
		}
		else
		{
			/*
			 * We're on a historical timeline, so limit reading to the switch
			 * point where we moved to the next timeline.
			 *
			 * We don't need to GetFlushRecPtr or GetXLogReplayRecPtr. We know
			 * about the new timeline, so we must've received past the end of
			 * it.
			 */
			read_upto = state->currTLIValidUntil;

			/*
			 * Setting ws_tli to our wanted record's TLI is slightly wrong;
			 * the page might begin on an older timeline if it contains a
			 * timeline switch, since its xlog segment will have been copied
			 * from the prior timeline. This is pretty harmless though, as
			 * nothing cares so long as the timeline doesn't go backwards.  We
			 * should read the page header instead; FIXME someday.
			 */
			state->seg.ws_tli = state->currTLI;

			/* No need to wait on a historical timeline */
			break;
		}
	}

	if (targetPagePtr + XLOG_BLCKSZ <= read_upto)
	{
		/*
		 * more than one block available; read only that block, have caller
		 * come back if they need more.
		 */
		count = XLOG_BLCKSZ;
	}
	else if (targetPagePtr + reqLen > read_upto)
	{
		/* not enough data there */
		return -1;
	}
	else
	{
		/* enough bytes available to satisfy the request */
		count = read_upto - targetPagePtr;
	}

	/*
	 * Even though we just determined how much of the page can be validly read
	 * as 'count', read the whole page anyway. It's guaranteed to be
	 * zero-padded up to the page boundary if it's incomplete.
	 */
	XLogRead(cur_page, state->segcxt.ws_segsize, state->seg.ws_tli, targetPagePtr,
			 XLOG_BLCKSZ);

	/* number of valid bytes in the buffer */
	return count;
}