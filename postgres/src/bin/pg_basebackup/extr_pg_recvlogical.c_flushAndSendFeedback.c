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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  OutputFsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feGetCurrentTimestamp () ; 
 int /*<<< orphan*/  sendFeedback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
flushAndSendFeedback(PGconn *conn, TimestampTz *now)
{
	/* flush data to disk, so that we send a recent flush pointer */
	if (!OutputFsync(*now))
		return false;
	*now = feGetCurrentTimestamp();
	if (!sendFeedback(conn, *now, true, false))
		return false;

	return true;
}