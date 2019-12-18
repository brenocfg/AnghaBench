#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct timeval {int tv_sec; int tv_usec; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ XLogRecPtr ;
typedef  scalar_t__ TimestampTz ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetConnection () ; 
 scalar_t__ InvalidXLogRecPtr ; 
 scalar_t__ Max (scalar_t__,scalar_t__) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  OutputFsync (scalar_t__) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_BOTH ; 
 scalar_t__ PGRES_COPY_OUT ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQconsumeInput (int /*<<< orphan*/ *) ; 
 int PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 int PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQsocket (int /*<<< orphan*/ *) ; 
 int S_IRUSR ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/ * conn ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 scalar_t__ endpos ; 
 scalar_t__ errno ; 
 scalar_t__ feGetCurrentTimestamp () ; 
 int /*<<< orphan*/  feTimestampDifference (scalar_t__,scalar_t__,long*,int*) ; 
 scalar_t__ feTimestampDifferenceExceeds (scalar_t__,scalar_t__,int) ; 
 scalar_t__ fe_recvint64 (char*) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushAndSendFeedback (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int fsync_interval ; 
 int /*<<< orphan*/  isatty (int) ; 
 int noptions ; 
 int open (int,int,int) ; 
 int /*<<< orphan*/ ** options ; 
 int outfd ; 
 int outfile ; 
 scalar_t__ output_fsync_lsn ; 
 int output_isfile ; 
 scalar_t__ output_last_fsync ; 
 int output_needs_fsync ; 
 int output_reopen ; 
 scalar_t__ output_written_lsn ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,...) ; 
 int /*<<< orphan*/  prepareToTerminate (int /*<<< orphan*/ *,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  replication_slot ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  sendFeedback (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int standby_message_timeout ; 
 int startpos ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int,char*) ; 
 int time_to_abort ; 
 scalar_t__ verbose ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
StreamLogicalLog(void)
{
	PGresult   *res;
	char	   *copybuf = NULL;
	TimestampTz last_status = -1;
	int			i;
	PQExpBuffer query;

	output_written_lsn = InvalidXLogRecPtr;
	output_fsync_lsn = InvalidXLogRecPtr;

	query = createPQExpBuffer();

	/*
	 * Connect in replication mode to the server
	 */
	if (!conn)
		conn = GetConnection();
	if (!conn)
		/* Error message already written in GetConnection() */
		return;

	/*
	 * Start the replication
	 */
	if (verbose)
		pg_log_info("starting log streaming at %X/%X (slot %s)",
					(uint32) (startpos >> 32), (uint32) startpos,
					replication_slot);

	/* Initiate the replication stream at specified location */
	appendPQExpBuffer(query, "START_REPLICATION SLOT \"%s\" LOGICAL %X/%X",
					  replication_slot, (uint32) (startpos >> 32), (uint32) startpos);

	/* print options if there are any */
	if (noptions)
		appendPQExpBufferStr(query, " (");

	for (i = 0; i < noptions; i++)
	{
		/* separator */
		if (i > 0)
			appendPQExpBufferStr(query, ", ");

		/* write option name */
		appendPQExpBuffer(query, "\"%s\"", options[(i * 2)]);

		/* write option value if specified */
		if (options[(i * 2) + 1] != NULL)
			appendPQExpBuffer(query, " '%s'", options[(i * 2) + 1]);
	}

	if (noptions)
		appendPQExpBufferChar(query, ')');

	res = PQexec(conn, query->data);
	if (PQresultStatus(res) != PGRES_COPY_BOTH)
	{
		pg_log_error("could not send replication command \"%s\": %s",
					 query->data, PQresultErrorMessage(res));
		PQclear(res);
		goto error;
	}
	PQclear(res);
	resetPQExpBuffer(query);

	if (verbose)
		pg_log_info("streaming initiated");

	while (!time_to_abort)
	{
		int			r;
		int			bytes_left;
		int			bytes_written;
		TimestampTz now;
		int			hdr_len;
		XLogRecPtr	cur_record_lsn = InvalidXLogRecPtr;

		if (copybuf != NULL)
		{
			PQfreemem(copybuf);
			copybuf = NULL;
		}

		/*
		 * Potentially send a status message to the master
		 */
		now = feGetCurrentTimestamp();

		if (outfd != -1 &&
			feTimestampDifferenceExceeds(output_last_fsync, now,
										 fsync_interval))
		{
			if (!OutputFsync(now))
				goto error;
		}

		if (standby_message_timeout > 0 &&
			feTimestampDifferenceExceeds(last_status, now,
										 standby_message_timeout))
		{
			/* Time to send feedback! */
			if (!sendFeedback(conn, now, true, false))
				goto error;

			last_status = now;
		}

		/* got SIGHUP, close output file */
		if (outfd != -1 && output_reopen && strcmp(outfile, "-") != 0)
		{
			now = feGetCurrentTimestamp();
			if (!OutputFsync(now))
				goto error;
			close(outfd);
			outfd = -1;
		}
		output_reopen = false;

		/* open the output file, if not open yet */
		if (outfd == -1)
		{
			struct stat statbuf;

			if (strcmp(outfile, "-") == 0)
				outfd = fileno(stdout);
			else
				outfd = open(outfile, O_CREAT | O_APPEND | O_WRONLY | PG_BINARY,
							 S_IRUSR | S_IWUSR);
			if (outfd == -1)
			{
				pg_log_error("could not open log file \"%s\": %m", outfile);
				goto error;
			}

			if (fstat(outfd, &statbuf) != 0)
				pg_log_error("could not stat file \"%s\": %m", outfile);

			output_isfile = S_ISREG(statbuf.st_mode) && !isatty(outfd);
		}

		r = PQgetCopyData(conn, &copybuf, 1);
		if (r == 0)
		{
			/*
			 * In async mode, and no data available. We block on reading but
			 * not more than the specified timeout, so that we can send a
			 * response back to the client.
			 */
			fd_set		input_mask;
			TimestampTz message_target = 0;
			TimestampTz fsync_target = 0;
			struct timeval timeout;
			struct timeval *timeoutptr = NULL;

			if (PQsocket(conn) < 0)
			{
				pg_log_error("invalid socket: %s", PQerrorMessage(conn));
				goto error;
			}

			FD_ZERO(&input_mask);
			FD_SET(PQsocket(conn), &input_mask);

			/* Compute when we need to wakeup to send a keepalive message. */
			if (standby_message_timeout)
				message_target = last_status + (standby_message_timeout - 1) *
					((int64) 1000);

			/* Compute when we need to wakeup to fsync the output file. */
			if (fsync_interval > 0 && output_needs_fsync)
				fsync_target = output_last_fsync + (fsync_interval - 1) *
					((int64) 1000);

			/* Now compute when to wakeup. */
			if (message_target > 0 || fsync_target > 0)
			{
				TimestampTz targettime;
				long		secs;
				int			usecs;

				targettime = message_target;

				if (fsync_target > 0 && fsync_target < targettime)
					targettime = fsync_target;

				feTimestampDifference(now,
									  targettime,
									  &secs,
									  &usecs);
				if (secs <= 0)
					timeout.tv_sec = 1; /* Always sleep at least 1 sec */
				else
					timeout.tv_sec = secs;
				timeout.tv_usec = usecs;
				timeoutptr = &timeout;
			}

			r = select(PQsocket(conn) + 1, &input_mask, NULL, NULL, timeoutptr);
			if (r == 0 || (r < 0 && errno == EINTR))
			{
				/*
				 * Got a timeout or signal. Continue the loop and either
				 * deliver a status packet to the server or just go back into
				 * blocking.
				 */
				continue;
			}
			else if (r < 0)
			{
				pg_log_error("select() failed: %m");
				goto error;
			}

			/* Else there is actually data on the socket */
			if (PQconsumeInput(conn) == 0)
			{
				pg_log_error("could not receive data from WAL stream: %s",
							 PQerrorMessage(conn));
				goto error;
			}
			continue;
		}

		/* End of copy stream */
		if (r == -1)
			break;

		/* Failure while reading the copy stream */
		if (r == -2)
		{
			pg_log_error("could not read COPY data: %s",
						 PQerrorMessage(conn));
			goto error;
		}

		/* Check the message type. */
		if (copybuf[0] == 'k')
		{
			int			pos;
			bool		replyRequested;
			XLogRecPtr	walEnd;
			bool		endposReached = false;

			/*
			 * Parse the keepalive message, enclosed in the CopyData message.
			 * We just check if the server requested a reply, and ignore the
			 * rest.
			 */
			pos = 1;			/* skip msgtype 'k' */
			walEnd = fe_recvint64(&copybuf[pos]);
			output_written_lsn = Max(walEnd, output_written_lsn);

			pos += 8;			/* read walEnd */

			pos += 8;			/* skip sendTime */

			if (r < pos + 1)
			{
				pg_log_error("streaming header too small: %d", r);
				goto error;
			}
			replyRequested = copybuf[pos];

			if (endpos != InvalidXLogRecPtr && walEnd >= endpos)
			{
				/*
				 * If there's nothing to read on the socket until a keepalive
				 * we know that the server has nothing to send us; and if
				 * walEnd has passed endpos, we know nothing else can have
				 * committed before endpos.  So we can bail out now.
				 */
				endposReached = true;
			}

			/* Send a reply, if necessary */
			if (replyRequested || endposReached)
			{
				if (!flushAndSendFeedback(conn, &now))
					goto error;
				last_status = now;
			}

			if (endposReached)
			{
				prepareToTerminate(conn, endpos, true, InvalidXLogRecPtr);
				time_to_abort = true;
				break;
			}

			continue;
		}
		else if (copybuf[0] != 'w')
		{
			pg_log_error("unrecognized streaming header: \"%c\"",
						 copybuf[0]);
			goto error;
		}

		/*
		 * Read the header of the XLogData message, enclosed in the CopyData
		 * message. We only need the WAL location field (dataStart), the rest
		 * of the header is ignored.
		 */
		hdr_len = 1;			/* msgtype 'w' */
		hdr_len += 8;			/* dataStart */
		hdr_len += 8;			/* walEnd */
		hdr_len += 8;			/* sendTime */
		if (r < hdr_len + 1)
		{
			pg_log_error("streaming header too small: %d", r);
			goto error;
		}

		/* Extract WAL location for this block */
		cur_record_lsn = fe_recvint64(&copybuf[1]);

		if (endpos != InvalidXLogRecPtr && cur_record_lsn > endpos)
		{
			/*
			 * We've read past our endpoint, so prepare to go away being
			 * cautious about what happens to our output data.
			 */
			if (!flushAndSendFeedback(conn, &now))
				goto error;
			prepareToTerminate(conn, endpos, false, cur_record_lsn);
			time_to_abort = true;
			break;
		}

		output_written_lsn = Max(cur_record_lsn, output_written_lsn);

		bytes_left = r - hdr_len;
		bytes_written = 0;

		/* signal that a fsync is needed */
		output_needs_fsync = true;

		while (bytes_left)
		{
			int			ret;

			ret = write(outfd,
						copybuf + hdr_len + bytes_written,
						bytes_left);

			if (ret < 0)
			{
				pg_log_error("could not write %u bytes to log file \"%s\": %m",
							 bytes_left, outfile);
				goto error;
			}

			/* Write was successful, advance our position */
			bytes_written += ret;
			bytes_left -= ret;
		}

		if (write(outfd, "\n", 1) != 1)
		{
			pg_log_error("could not write %u bytes to log file \"%s\": %m",
						 1, outfile);
			goto error;
		}

		if (endpos != InvalidXLogRecPtr && cur_record_lsn == endpos)
		{
			/* endpos was exactly the record we just processed, we're done */
			if (!flushAndSendFeedback(conn, &now))
				goto error;
			prepareToTerminate(conn, endpos, false, cur_record_lsn);
			time_to_abort = true;
			break;
		}
	}

	res = PQgetResult(conn);
	if (PQresultStatus(res) == PGRES_COPY_OUT)
	{
		/*
		 * We're doing a client-initiated clean exit and have sent CopyDone to
		 * the server. We've already sent replay confirmation and fsync'd so
		 * we can just clean up the connection now.
		 */
		goto error;
	}
	else if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		pg_log_error("unexpected termination of replication stream: %s",
					 PQresultErrorMessage(res));
		goto error;
	}
	PQclear(res);

	if (outfd != -1 && strcmp(outfile, "-") != 0)
	{
		TimestampTz t = feGetCurrentTimestamp();

		/* no need to jump to error on failure here, we're finishing anyway */
		OutputFsync(t);

		if (close(outfd) != 0)
			pg_log_error("could not close file \"%s\": %m", outfile);
	}
	outfd = -1;
error:
	if (copybuf != NULL)
	{
		PQfreemem(copybuf);
		copybuf = NULL;
	}
	destroyPQExpBuffer(query);
	PQfinish(conn);
	conn = NULL;
}