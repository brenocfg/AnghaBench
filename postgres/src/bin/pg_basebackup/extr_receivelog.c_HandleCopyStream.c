#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int TimestampTz ;
struct TYPE_9__ {int /*<<< orphan*/  stop_socket; int /*<<< orphan*/  standby_message_timeout; TYPE_1__* walmethod; scalar_t__ synchronous; int /*<<< orphan*/  startpos; } ;
struct TYPE_8__ {scalar_t__ (* sync ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getlasterror ) () ;} ;
typedef  TYPE_2__ StreamCtl ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 long CalculateCopyStreamSleeptime (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CheckCopyStreamStop (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CopyStreamReceive (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * HandleEndOfCopyStream (int /*<<< orphan*/ *,TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int /*<<< orphan*/  ProcessKeepaliveMsg (int /*<<< orphan*/ *,TYPE_2__*,char*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ProcessXLogDataMsg (int /*<<< orphan*/ *,TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_walfile_name ; 
 int /*<<< orphan*/  exit (int) ; 
 int feGetCurrentTimestamp () ; 
 scalar_t__ feTimestampDifferenceExceeds (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lastFlushPosition ; 
 int /*<<< orphan*/  pg_log_error (char*,char) ; 
 int /*<<< orphan*/  pg_log_fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendFeedback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int still_sending ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/ * walfile ; 

__attribute__((used)) static PGresult *
HandleCopyStream(PGconn *conn, StreamCtl *stream,
				 XLogRecPtr *stoppos)
{
	char	   *copybuf = NULL;
	TimestampTz last_status = -1;
	XLogRecPtr	blockpos = stream->startpos;

	still_sending = true;

	while (1)
	{
		int			r;
		TimestampTz now;
		long		sleeptime;

		/*
		 * Check if we should continue streaming, or abort at this point.
		 */
		if (!CheckCopyStreamStop(conn, stream, blockpos, stoppos))
			goto error;

		now = feGetCurrentTimestamp();

		/*
		 * If synchronous option is true, issue sync command as soon as there
		 * are WAL data which has not been flushed yet.
		 */
		if (stream->synchronous && lastFlushPosition < blockpos && walfile != NULL)
		{
			if (stream->walmethod->sync(walfile) != 0)
			{
				pg_log_fatal("could not fsync file \"%s\": %s",
							 current_walfile_name, stream->walmethod->getlasterror());
				exit(1);
			}
			lastFlushPosition = blockpos;

			/*
			 * Send feedback so that the server sees the latest WAL locations
			 * immediately.
			 */
			if (!sendFeedback(conn, blockpos, now, false))
				goto error;
			last_status = now;
		}

		/*
		 * Potentially send a status message to the master
		 */
		if (still_sending && stream->standby_message_timeout > 0 &&
			feTimestampDifferenceExceeds(last_status, now,
										 stream->standby_message_timeout))
		{
			/* Time to send feedback! */
			if (!sendFeedback(conn, blockpos, now, false))
				goto error;
			last_status = now;
		}

		/*
		 * Calculate how long send/receive loops should sleep
		 */
		sleeptime = CalculateCopyStreamSleeptime(now, stream->standby_message_timeout,
												 last_status);

		r = CopyStreamReceive(conn, sleeptime, stream->stop_socket, &copybuf);
		while (r != 0)
		{
			if (r == -1)
				goto error;
			if (r == -2)
			{
				PGresult   *res = HandleEndOfCopyStream(conn, stream, copybuf, blockpos, stoppos);

				if (res == NULL)
					goto error;
				else
					return res;
			}

			/* Check the message type. */
			if (copybuf[0] == 'k')
			{
				if (!ProcessKeepaliveMsg(conn, stream, copybuf, r, blockpos,
										 &last_status))
					goto error;
			}
			else if (copybuf[0] == 'w')
			{
				if (!ProcessXLogDataMsg(conn, stream, copybuf, r, &blockpos))
					goto error;

				/*
				 * Check if we should continue streaming, or abort at this
				 * point.
				 */
				if (!CheckCopyStreamStop(conn, stream, blockpos, stoppos))
					goto error;
			}
			else
			{
				pg_log_error("unrecognized streaming header: \"%c\"",
							 copybuf[0]);
				goto error;
			}

			/*
			 * Process the received data, and any subsequent data we can read
			 * without blocking.
			 */
			r = CopyStreamReceive(conn, 0, stream->stop_socket, &copybuf);
		}
	}

error:
	if (copybuf != NULL)
		PQfreemem(copybuf);
	return NULL;
}