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

/* Variables and functions */
 int /*<<< orphan*/  COMMERROR ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  ProcessStandbyMessage () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  last_processing ; 
 int /*<<< orphan*/  last_reply_timestamp ; 
 int /*<<< orphan*/  pq_endmsgread () ; 
 int pq_getbyte_if_available (unsigned char*) ; 
 scalar_t__ pq_getmessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_putmessage_noblock (char,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_startmsgread () ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_message ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ *) ; 
 int streamingDoneReceiving ; 
 int streamingDoneSending ; 
 int waiting_for_ping_response ; 

__attribute__((used)) static void
ProcessRepliesIfAny(void)
{
	unsigned char firstchar;
	int			r;
	bool		received = false;

	last_processing = GetCurrentTimestamp();

	for (;;)
	{
		pq_startmsgread();
		r = pq_getbyte_if_available(&firstchar);
		if (r < 0)
		{
			/* unexpected error or EOF */
			ereport(COMMERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("unexpected EOF on standby connection")));
			proc_exit(0);
		}
		if (r == 0)
		{
			/* no data available without blocking */
			pq_endmsgread();
			break;
		}

		/* Read the message contents */
		resetStringInfo(&reply_message);
		if (pq_getmessage(&reply_message, 0))
		{
			ereport(COMMERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("unexpected EOF on standby connection")));
			proc_exit(0);
		}

		/*
		 * If we already received a CopyDone from the frontend, the frontend
		 * should not send us anything until we've closed our end of the COPY.
		 * XXX: In theory, the frontend could already send the next command
		 * before receiving the CopyDone, but libpq doesn't currently allow
		 * that.
		 */
		if (streamingDoneReceiving && firstchar != 'X')
			ereport(FATAL,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("unexpected standby message type \"%c\", after receiving CopyDone",
							firstchar)));

		/* Handle the very limited subset of commands expected in this phase */
		switch (firstchar)
		{
				/*
				 * 'd' means a standby reply wrapped in a CopyData packet.
				 */
			case 'd':
				ProcessStandbyMessage();
				received = true;
				break;

				/*
				 * CopyDone means the standby requested to finish streaming.
				 * Reply with CopyDone, if we had not sent that already.
				 */
			case 'c':
				if (!streamingDoneSending)
				{
					pq_putmessage_noblock('c', NULL, 0);
					streamingDoneSending = true;
				}

				streamingDoneReceiving = true;
				received = true;
				break;

				/*
				 * 'X' means that the standby is closing down the socket.
				 */
			case 'X':
				proc_exit(0);

			default:
				ereport(FATAL,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("invalid standby message type \"%c\"",
								firstchar)));
		}
	}

	/*
	 * Save the last reply timestamp if we've received at least one reply.
	 */
	if (received)
	{
		last_reply_timestamp = last_processing;
		waiting_for_ping_response = false;
	}
}