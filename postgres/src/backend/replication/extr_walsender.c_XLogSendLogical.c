#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecord ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_7__ {scalar_t__ sentPtr; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ WalSnd ;
struct TYPE_9__ {scalar_t__ EndRecPtr; } ;
struct TYPE_8__ {TYPE_3__* reader; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetFlushRecPtr () ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LogicalDecodingProcessRecord (TYPE_2__*,TYPE_3__*) ; 
 TYPE_1__* MyWalSnd ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int WalSndCaughtUp ; 
 int /*<<< orphan*/ * XLogReadRecord (TYPE_3__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int got_SIGUSR2 ; 
 scalar_t__ got_STOPPING ; 
 TYPE_2__* logical_decoding_ctx ; 
 int /*<<< orphan*/  logical_startptr ; 
 scalar_t__ sentPtr ; 

__attribute__((used)) static void
XLogSendLogical(void)
{
	XLogRecord *record;
	char	   *errm;
	XLogRecPtr	flushPtr;

	/*
	 * Don't know whether we've caught up yet. We'll set WalSndCaughtUp to
	 * true in WalSndWaitForWal, if we're actually waiting. We also set to
	 * true if XLogReadRecord() had to stop reading but WalSndWaitForWal
	 * didn't wait - i.e. when we're shutting down.
	 */
	WalSndCaughtUp = false;

	record = XLogReadRecord(logical_decoding_ctx->reader, logical_startptr, &errm);
	logical_startptr = InvalidXLogRecPtr;

	/* xlog record was invalid */
	if (errm != NULL)
		elog(ERROR, "%s", errm);

	/*
	 * We'll use the current flush point to determine whether we've caught up.
	 */
	flushPtr = GetFlushRecPtr();

	if (record != NULL)
	{
		/*
		 * Note the lack of any call to LagTrackerWrite() which is handled by
		 * WalSndUpdateProgress which is called by output plugin through
		 * logical decoding write api.
		 */
		LogicalDecodingProcessRecord(logical_decoding_ctx, logical_decoding_ctx->reader);

		sentPtr = logical_decoding_ctx->reader->EndRecPtr;
	}

	/* Set flag if we're caught up. */
	if (logical_decoding_ctx->reader->EndRecPtr >= flushPtr)
		WalSndCaughtUp = true;

	/*
	 * If we're caught up and have been requested to stop, have WalSndLoop()
	 * terminate the connection in an orderly manner, after writing out all
	 * the pending data.
	 */
	if (WalSndCaughtUp && got_STOPPING)
		got_SIGUSR2 = true;

	/* Update shared memory status */
	{
		WalSnd	   *walsnd = MyWalSnd;

		SpinLockAcquire(&walsnd->mutex);
		walsnd->sentPtr = sentPtr;
		SpinLockRelease(&walsnd->mutex);
	}
}