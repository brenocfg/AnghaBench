#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  query ;
typedef  int XLogRecPtr ;
struct TYPE_8__ {char* replication_slot; scalar_t__ timeline; int startpos; TYPE_1__* walmethod; scalar_t__ (* stream_stop ) (int,int,int) ;int /*<<< orphan*/ * sysidentifier; scalar_t__ synchronous; } ;
struct TYPE_7__ {scalar_t__ (* close ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int (* getlasterror ) () ;} ;
typedef  TYPE_2__ StreamCtl ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NO_RENAME ; 
 int /*<<< orphan*/  CheckServerVersionForStreaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HandleCopyStream (int /*<<< orphan*/ *,TYPE_2__*,int*) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_COPY_BOTH ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int ReadEndOfStreamingResult (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  WalSegSz ; 
 int XLogSegmentOffset (int,int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int current_walfile_name ; 
 int /*<<< orphan*/  existsTimeLineHistoryFile (TYPE_2__*) ; 
 int lastFlushPosition ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_warning (char*,int,int,int,int) ; 
 int reportFlushPosition ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int,int,int) ; 
 scalar_t__ stub2 (int,int,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub4 () ; 
 int /*<<< orphan*/ * walfile ; 
 int /*<<< orphan*/  writeTimeLineHistoryFile (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ReceiveXlogStream(PGconn *conn, StreamCtl *stream)
{
	char		query[128];
	char		slotcmd[128];
	PGresult   *res;
	XLogRecPtr	stoppos;

	/*
	 * The caller should've checked the server version already, but doesn't do
	 * any harm to check it here too.
	 */
	if (!CheckServerVersionForStreaming(conn))
		return false;

	/*
	 * Decide whether we want to report the flush position. If we report the
	 * flush position, the primary will know what WAL we'll possibly
	 * re-request, and it can then remove older WAL safely. We must always do
	 * that when we are using slots.
	 *
	 * Reporting the flush position makes one eligible as a synchronous
	 * replica. People shouldn't include generic names in
	 * synchronous_standby_names, but we've protected them against it so far,
	 * so let's continue to do so unless specifically requested.
	 */
	if (stream->replication_slot != NULL)
	{
		reportFlushPosition = true;
		sprintf(slotcmd, "SLOT \"%s\" ", stream->replication_slot);
	}
	else
	{
		if (stream->synchronous)
			reportFlushPosition = true;
		else
			reportFlushPosition = false;
		slotcmd[0] = 0;
	}

	if (stream->sysidentifier != NULL)
	{
		/* Validate system identifier hasn't changed */
		res = PQexec(conn, "IDENTIFY_SYSTEM");
		if (PQresultStatus(res) != PGRES_TUPLES_OK)
		{
			pg_log_error("could not send replication command \"%s\": %s",
						 "IDENTIFY_SYSTEM", PQerrorMessage(conn));
			PQclear(res);
			return false;
		}
		if (PQntuples(res) != 1 || PQnfields(res) < 3)
		{
			pg_log_error("could not identify system: got %d rows and %d fields, expected %d rows and %d or more fields",
						 PQntuples(res), PQnfields(res), 1, 3);
			PQclear(res);
			return false;
		}
		if (strcmp(stream->sysidentifier, PQgetvalue(res, 0, 0)) != 0)
		{
			pg_log_error("system identifier does not match between base backup and streaming connection");
			PQclear(res);
			return false;
		}
		if (stream->timeline > atoi(PQgetvalue(res, 0, 1)))
		{
			pg_log_error("starting timeline %u is not present in the server",
						 stream->timeline);
			PQclear(res);
			return false;
		}
		PQclear(res);
	}

	/*
	 * initialize flush position to starting point, it's the caller's
	 * responsibility that that's sane.
	 */
	lastFlushPosition = stream->startpos;

	while (1)
	{
		/*
		 * Fetch the timeline history file for this timeline, if we don't have
		 * it already. When streaming log to tar, this will always return
		 * false, as we are never streaming into an existing file and
		 * therefore there can be no pre-existing timeline history file.
		 */
		if (!existsTimeLineHistoryFile(stream))
		{
			snprintf(query, sizeof(query), "TIMELINE_HISTORY %u", stream->timeline);
			res = PQexec(conn, query);
			if (PQresultStatus(res) != PGRES_TUPLES_OK)
			{
				/* FIXME: we might send it ok, but get an error */
				pg_log_error("could not send replication command \"%s\": %s",
							 "TIMELINE_HISTORY", PQresultErrorMessage(res));
				PQclear(res);
				return false;
			}

			/*
			 * The response to TIMELINE_HISTORY is a single row result set
			 * with two fields: filename and content
			 */
			if (PQnfields(res) != 2 || PQntuples(res) != 1)
			{
				pg_log_warning("unexpected response to TIMELINE_HISTORY command: got %d rows and %d fields, expected %d rows and %d fields",
							   PQntuples(res), PQnfields(res), 1, 2);
			}

			/* Write the history file to disk */
			writeTimeLineHistoryFile(stream,
									 PQgetvalue(res, 0, 0),
									 PQgetvalue(res, 0, 1));

			PQclear(res);
		}

		/*
		 * Before we start streaming from the requested location, check if the
		 * callback tells us to stop here.
		 */
		if (stream->stream_stop(stream->startpos, stream->timeline, false))
			return true;

		/* Initiate the replication stream at specified location */
		snprintf(query, sizeof(query), "START_REPLICATION %s%X/%X TIMELINE %u",
				 slotcmd,
				 (uint32) (stream->startpos >> 32), (uint32) stream->startpos,
				 stream->timeline);
		res = PQexec(conn, query);
		if (PQresultStatus(res) != PGRES_COPY_BOTH)
		{
			pg_log_error("could not send replication command \"%s\": %s",
						 "START_REPLICATION", PQresultErrorMessage(res));
			PQclear(res);
			return false;
		}
		PQclear(res);

		/* Stream the WAL */
		res = HandleCopyStream(conn, stream, &stoppos);
		if (res == NULL)
			goto error;

		/*
		 * Streaming finished.
		 *
		 * There are two possible reasons for that: a controlled shutdown, or
		 * we reached the end of the current timeline. In case of
		 * end-of-timeline, the server sends a result set after Copy has
		 * finished, containing information about the next timeline. Read
		 * that, and restart streaming from the next timeline. In case of
		 * controlled shutdown, stop here.
		 */
		if (PQresultStatus(res) == PGRES_TUPLES_OK)
		{
			/*
			 * End-of-timeline. Read the next timeline's ID and starting
			 * position. Usually, the starting position will match the end of
			 * the previous timeline, but there are corner cases like if the
			 * server had sent us half of a WAL record, when it was promoted.
			 * The new timeline will begin at the end of the last complete
			 * record in that case, overlapping the partial WAL record on the
			 * old timeline.
			 */
			uint32		newtimeline;
			bool		parsed;

			parsed = ReadEndOfStreamingResult(res, &stream->startpos, &newtimeline);
			PQclear(res);
			if (!parsed)
				goto error;

			/* Sanity check the values the server gave us */
			if (newtimeline <= stream->timeline)
			{
				pg_log_error("server reported unexpected next timeline %u, following timeline %u",
							 newtimeline, stream->timeline);
				goto error;
			}
			if (stream->startpos > stoppos)
			{
				pg_log_error("server stopped streaming timeline %u at %X/%X, but reported next timeline %u to begin at %X/%X",
							 stream->timeline, (uint32) (stoppos >> 32), (uint32) stoppos,
							 newtimeline, (uint32) (stream->startpos >> 32), (uint32) stream->startpos);
				goto error;
			}

			/* Read the final result, which should be CommandComplete. */
			res = PQgetResult(conn);
			if (PQresultStatus(res) != PGRES_COMMAND_OK)
			{
				pg_log_error("unexpected termination of replication stream: %s",
							 PQresultErrorMessage(res));
				PQclear(res);
				goto error;
			}
			PQclear(res);

			/*
			 * Loop back to start streaming from the new timeline. Always
			 * start streaming at the beginning of a segment.
			 */
			stream->timeline = newtimeline;
			stream->startpos = stream->startpos -
				XLogSegmentOffset(stream->startpos, WalSegSz);
			continue;
		}
		else if (PQresultStatus(res) == PGRES_COMMAND_OK)
		{
			PQclear(res);

			/*
			 * End of replication (ie. controlled shut down of the server).
			 *
			 * Check if the callback thinks it's OK to stop here. If not,
			 * complain.
			 */
			if (stream->stream_stop(stoppos, stream->timeline, false))
				return true;
			else
			{
				pg_log_error("replication stream was terminated before stop point");
				goto error;
			}
		}
		else
		{
			/* Server returned an error. */
			pg_log_error("unexpected termination of replication stream: %s",
						 PQresultErrorMessage(res));
			PQclear(res);
			goto error;
		}
	}

error:
	if (walfile != NULL && stream->walmethod->close(walfile, CLOSE_NO_RENAME) != 0)
		pg_log_error("could not close file \"%s\": %s",
					 current_walfile_name, stream->walmethod->getlasterror());
	walfile = NULL;
	return false;
}