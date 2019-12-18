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
typedef  int /*<<< orphan*/  StreamCtl ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ PGRES_COPY_IN ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 scalar_t__ PQputCopyEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_walfile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int still_sending ; 

__attribute__((used)) static PGresult *
HandleEndOfCopyStream(PGconn *conn, StreamCtl *stream, char *copybuf,
					  XLogRecPtr blockpos, XLogRecPtr *stoppos)
{
	PGresult   *res = PQgetResult(conn);

	/*
	 * The server closed its end of the copy stream.  If we haven't closed
	 * ours already, we need to do so now, unless the server threw an error,
	 * in which case we don't.
	 */
	if (still_sending)
	{
		if (!close_walfile(stream, blockpos))
		{
			/* Error message written in close_walfile() */
			PQclear(res);
			return NULL;
		}
		if (PQresultStatus(res) == PGRES_COPY_IN)
		{
			if (PQputCopyEnd(conn, NULL) <= 0 || PQflush(conn))
			{
				pg_log_error("could not send copy-end packet: %s",
							 PQerrorMessage(conn));
				PQclear(res);
				return NULL;
			}
			res = PQgetResult(conn);
		}
		still_sending = false;
	}
	if (copybuf != NULL)
		PQfreemem(copybuf);
	*stoppos = blockpos;
	return res;
}