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
 scalar_t__ TimestampTzPlusMilliseconds (scalar_t__,int) ; 
 int /*<<< orphan*/  WalSndKeepalive (int) ; 
 int /*<<< orphan*/  WalSndShutdown () ; 
 scalar_t__ last_processing ; 
 scalar_t__ last_reply_timestamp ; 
 scalar_t__ pq_flush_if_writable () ; 
 int waiting_for_ping_response ; 
 int wal_sender_timeout ; 

__attribute__((used)) static void
WalSndKeepaliveIfNecessary(void)
{
	TimestampTz ping_time;

	/*
	 * Don't send keepalive messages if timeouts are globally disabled or
	 * we're doing something not partaking in timeouts.
	 */
	if (wal_sender_timeout <= 0 || last_reply_timestamp <= 0)
		return;

	if (waiting_for_ping_response)
		return;

	/*
	 * If half of wal_sender_timeout has lapsed without receiving any reply
	 * from the standby, send a keep-alive message to the standby requesting
	 * an immediate reply.
	 */
	ping_time = TimestampTzPlusMilliseconds(last_reply_timestamp,
											wal_sender_timeout / 2);
	if (last_processing >= ping_time)
	{
		WalSndKeepalive(true);
		waiting_for_ping_response = true;

		/* Try to flush pending output to the client */
		if (pq_flush_if_writable() != 0)
			WalSndShutdown();
	}
}