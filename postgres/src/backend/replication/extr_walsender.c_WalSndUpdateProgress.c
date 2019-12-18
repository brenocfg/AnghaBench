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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  LagTrackerWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TimestampDifferenceExceeds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WALSND_LOGICAL_LAG_TRACK_INTERVAL_MS ; 

__attribute__((used)) static void
WalSndUpdateProgress(LogicalDecodingContext *ctx, XLogRecPtr lsn, TransactionId xid)
{
	static TimestampTz sendTime = 0;
	TimestampTz now = GetCurrentTimestamp();

	/*
	 * Track lag no more than once per WALSND_LOGICAL_LAG_TRACK_INTERVAL_MS to
	 * avoid flooding the lag tracker when we commit frequently.
	 */
#define WALSND_LOGICAL_LAG_TRACK_INTERVAL_MS	1000
	if (!TimestampDifferenceExceeds(sendTime, now,
									WALSND_LOGICAL_LAG_TRACK_INTERVAL_MS))
		return;

	LagTrackerWrite(lsn, now);
	sendTime = now;
}