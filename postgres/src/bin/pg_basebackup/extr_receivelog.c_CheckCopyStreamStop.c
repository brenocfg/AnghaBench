#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_4__ {int /*<<< orphan*/  timeline; scalar_t__ (* stream_stop ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ StreamCtl ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQflush (int /*<<< orphan*/ *) ; 
 scalar_t__ PQputCopyEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_walfile (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int still_sending ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
CheckCopyStreamStop(PGconn *conn, StreamCtl *stream, XLogRecPtr blockpos,
					XLogRecPtr *stoppos)
{
	if (still_sending && stream->stream_stop(blockpos, stream->timeline, false))
	{
		if (!close_walfile(stream, blockpos))
		{
			/* Potential error message is written by close_walfile */
			return false;
		}
		if (PQputCopyEnd(conn, NULL) <= 0 || PQflush(conn))
		{
			pg_log_error("could not send copy-end packet: %s",
						 PQerrorMessage(conn));
			return false;
		}
		still_sending = false;
	}

	return true;
}