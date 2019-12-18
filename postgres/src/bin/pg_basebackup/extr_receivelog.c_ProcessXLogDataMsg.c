#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  timeline; scalar_t__ (* stream_stop ) (int,int /*<<< orphan*/ ,int) ;TYPE_1__* walmethod; } ;
struct TYPE_6__ {int (* get_current_pos ) (int /*<<< orphan*/ *) ;int (* write ) (int /*<<< orphan*/ *,char*,int) ;int /*<<< orphan*/  (* getlasterror ) () ;} ;
typedef  TYPE_2__ StreamCtl ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int PQerrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQflush (int /*<<< orphan*/ *) ; 
 scalar_t__ PQputCopyEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WalSegSz ; 
 int XLogSegmentOffset (int,int) ; 
 int /*<<< orphan*/  close_walfile (TYPE_2__*,int) ; 
 int /*<<< orphan*/  current_walfile_name ; 
 int fe_recvint64 (char*) ; 
 int /*<<< orphan*/  open_walfile (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pg_log_error (char*,int,...) ; 
 int still_sending ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stub4 () ; 
 scalar_t__ stub5 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * walfile ; 

__attribute__((used)) static bool
ProcessXLogDataMsg(PGconn *conn, StreamCtl *stream, char *copybuf, int len,
				   XLogRecPtr *blockpos)
{
	int			xlogoff;
	int			bytes_left;
	int			bytes_written;
	int			hdr_len;

	/*
	 * Once we've decided we don't want to receive any more, just ignore any
	 * subsequent XLogData messages.
	 */
	if (!(still_sending))
		return true;

	/*
	 * Read the header of the XLogData message, enclosed in the CopyData
	 * message. We only need the WAL location field (dataStart), the rest of
	 * the header is ignored.
	 */
	hdr_len = 1;				/* msgtype 'w' */
	hdr_len += 8;				/* dataStart */
	hdr_len += 8;				/* walEnd */
	hdr_len += 8;				/* sendTime */
	if (len < hdr_len)
	{
		pg_log_error("streaming header too small: %d", len);
		return false;
	}
	*blockpos = fe_recvint64(&copybuf[1]);

	/* Extract WAL location for this block */
	xlogoff = XLogSegmentOffset(*blockpos, WalSegSz);

	/*
	 * Verify that the initial location in the stream matches where we think
	 * we are.
	 */
	if (walfile == NULL)
	{
		/* No file open yet */
		if (xlogoff != 0)
		{
			pg_log_error("received write-ahead log record for offset %u with no file open",
						 xlogoff);
			return false;
		}
	}
	else
	{
		/* More data in existing segment */
		if (stream->walmethod->get_current_pos(walfile) != xlogoff)
		{
			pg_log_error("got WAL data offset %08x, expected %08x",
						 xlogoff, (int) stream->walmethod->get_current_pos(walfile));
			return false;
		}
	}

	bytes_left = len - hdr_len;
	bytes_written = 0;

	while (bytes_left)
	{
		int			bytes_to_write;

		/*
		 * If crossing a WAL boundary, only write up until we reach wal
		 * segment size.
		 */
		if (xlogoff + bytes_left > WalSegSz)
			bytes_to_write = WalSegSz - xlogoff;
		else
			bytes_to_write = bytes_left;

		if (walfile == NULL)
		{
			if (!open_walfile(stream, *blockpos))
			{
				/* Error logged by open_walfile */
				return false;
			}
		}

		if (stream->walmethod->write(walfile, copybuf + hdr_len + bytes_written,
									 bytes_to_write) != bytes_to_write)
		{
			pg_log_error("could not write %u bytes to WAL file \"%s\": %s",
						 bytes_to_write, current_walfile_name,
						 stream->walmethod->getlasterror());
			return false;
		}

		/* Write was successful, advance our position */
		bytes_written += bytes_to_write;
		bytes_left -= bytes_to_write;
		*blockpos += bytes_to_write;
		xlogoff += bytes_to_write;

		/* Did we reach the end of a WAL segment? */
		if (XLogSegmentOffset(*blockpos, WalSegSz) == 0)
		{
			if (!close_walfile(stream, *blockpos))
				/* Error message written in close_walfile() */
				return false;

			xlogoff = 0;

			if (still_sending && stream->stream_stop(*blockpos, stream->timeline, true))
			{
				if (PQputCopyEnd(conn, NULL) <= 0 || PQflush(conn))
				{
					pg_log_error("could not send copy-end packet: %s",
								 PQerrorMessage(conn));
					return false;
				}
				still_sending = false;
				return true;	/* ignore the rest of this XLogData packet */
			}
		}
	}
	/* No more data left to write, receive next copy packet */

	return true;
}