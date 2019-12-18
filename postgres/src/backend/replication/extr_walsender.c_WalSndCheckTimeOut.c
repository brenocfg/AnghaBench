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
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  COMMERROR ; 
 scalar_t__ TimestampTzPlusMilliseconds (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WalSndShutdown () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ last_processing ; 
 scalar_t__ last_reply_timestamp ; 
 scalar_t__ wal_sender_timeout ; 

__attribute__((used)) static void
WalSndCheckTimeOut(void)
{
	TimestampTz timeout;

	/* don't bail out if we're doing something that doesn't require timeouts */
	if (last_reply_timestamp <= 0)
		return;

	timeout = TimestampTzPlusMilliseconds(last_reply_timestamp,
										  wal_sender_timeout);

	if (wal_sender_timeout > 0 && last_processing >= timeout)
	{
		/*
		 * Since typically expiration of replication timeout means
		 * communication problem, we don't send the error message to the
		 * standby.
		 */
		ereport(COMMERROR,
				(errmsg("terminating walsender process due to replication timeout")));

		WalSndShutdown();
	}
}