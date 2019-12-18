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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQflush (int /*<<< orphan*/ *) ; 
 scalar_t__ PQputCopyData (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fe_sendint64 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lastFlushPosition ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ reportFlushPosition ; 

__attribute__((used)) static bool
sendFeedback(PGconn *conn, XLogRecPtr blockpos, TimestampTz now, bool replyRequested)
{
	char		replybuf[1 + 8 + 8 + 8 + 8 + 1];
	int			len = 0;

	replybuf[len] = 'r';
	len += 1;
	fe_sendint64(blockpos, &replybuf[len]); /* write */
	len += 8;
	if (reportFlushPosition)
		fe_sendint64(lastFlushPosition, &replybuf[len]);	/* flush */
	else
		fe_sendint64(InvalidXLogRecPtr, &replybuf[len]);	/* flush */
	len += 8;
	fe_sendint64(InvalidXLogRecPtr, &replybuf[len]);	/* apply */
	len += 8;
	fe_sendint64(now, &replybuf[len]);	/* sendTime */
	len += 8;
	replybuf[len] = replyRequested ? 1 : 0; /* replyRequested */
	len += 1;

	if (PQputCopyData(conn, replybuf, len) <= 0 || PQflush(conn))
	{
		pg_log_error("could not send feedback packet: %s",
					 PQerrorMessage(conn));
		return false;
	}

	return true;
}