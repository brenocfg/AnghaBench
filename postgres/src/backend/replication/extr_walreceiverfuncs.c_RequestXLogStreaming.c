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
typedef  int /*<<< orphan*/  pg_time_t ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_3__ {scalar_t__ walRcvState; char* conninfo; char* slotname; scalar_t__ receiveStart; scalar_t__ receivedTLI; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * latch; scalar_t__ receiveStartTLI; scalar_t__ latestChunkStart; scalar_t__ receivedUpto; int /*<<< orphan*/  startTime; } ;
typedef  TYPE_1__ WalRcvData ;
typedef  scalar_t__ TimeLineID ;
typedef  int /*<<< orphan*/  Latch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MAXCONNINFO ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  PMSIGNAL_START_WALRECEIVER ; 
 int /*<<< orphan*/  SendPostmasterSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ WALRCV_RESTARTING ; 
 scalar_t__ WALRCV_STARTING ; 
 scalar_t__ WALRCV_STOPPED ; 
 scalar_t__ WALRCV_WAITING ; 
 TYPE_1__* WalRcv ; 
 scalar_t__ XLogSegmentOffset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wal_segment_size ; 

void
RequestXLogStreaming(TimeLineID tli, XLogRecPtr recptr, const char *conninfo,
					 const char *slotname)
{
	WalRcvData *walrcv = WalRcv;
	bool		launch = false;
	pg_time_t	now = (pg_time_t) time(NULL);
	Latch	   *latch;

	/*
	 * We always start at the beginning of the segment. That prevents a broken
	 * segment (i.e., with no records in the first half of a segment) from
	 * being created by XLOG streaming, which might cause trouble later on if
	 * the segment is e.g archived.
	 */
	if (XLogSegmentOffset(recptr, wal_segment_size) != 0)
		recptr -= XLogSegmentOffset(recptr, wal_segment_size);

	SpinLockAcquire(&walrcv->mutex);

	/* It better be stopped if we try to restart it */
	Assert(walrcv->walRcvState == WALRCV_STOPPED ||
		   walrcv->walRcvState == WALRCV_WAITING);

	if (conninfo != NULL)
		strlcpy((char *) walrcv->conninfo, conninfo, MAXCONNINFO);
	else
		walrcv->conninfo[0] = '\0';

	if (slotname != NULL)
		strlcpy((char *) walrcv->slotname, slotname, NAMEDATALEN);
	else
		walrcv->slotname[0] = '\0';

	if (walrcv->walRcvState == WALRCV_STOPPED)
	{
		launch = true;
		walrcv->walRcvState = WALRCV_STARTING;
	}
	else
		walrcv->walRcvState = WALRCV_RESTARTING;
	walrcv->startTime = now;

	/*
	 * If this is the first startup of walreceiver (on this timeline),
	 * initialize receivedUpto and latestChunkStart to the starting point.
	 */
	if (walrcv->receiveStart == 0 || walrcv->receivedTLI != tli)
	{
		walrcv->receivedUpto = recptr;
		walrcv->receivedTLI = tli;
		walrcv->latestChunkStart = recptr;
	}
	walrcv->receiveStart = recptr;
	walrcv->receiveStartTLI = tli;

	latch = walrcv->latch;

	SpinLockRelease(&walrcv->mutex);

	if (launch)
		SendPostmasterSignal(PMSIGNAL_START_WALRECEIVER);
	else if (latch)
		SetLatch(latch);
}