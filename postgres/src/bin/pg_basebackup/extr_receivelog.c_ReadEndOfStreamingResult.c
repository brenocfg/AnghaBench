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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,int,...) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*) ; 

__attribute__((used)) static bool
ReadEndOfStreamingResult(PGresult *res, XLogRecPtr *startpos, uint32 *timeline)
{
	uint32		startpos_xlogid,
				startpos_xrecoff;

	/*----------
	 * The result set consists of one row and two columns, e.g:
	 *
	 *	next_tli | next_tli_startpos
	 * ----------+-------------------
	 *		   4 | 0/9949AE0
	 *
	 * next_tli is the timeline ID of the next timeline after the one that
	 * just finished streaming. next_tli_startpos is the WAL location where
	 * the server switched to it.
	 *----------
	 */
	if (PQnfields(res) < 2 || PQntuples(res) != 1)
	{
		pg_log_error("unexpected result set after end-of-timeline: got %d rows and %d fields, expected %d rows and %d fields",
					 PQntuples(res), PQnfields(res), 1, 2);
		return false;
	}

	*timeline = atoi(PQgetvalue(res, 0, 0));
	if (sscanf(PQgetvalue(res, 0, 1), "%X/%X", &startpos_xlogid,
			   &startpos_xrecoff) != 2)
	{
		pg_log_error("could not parse next timeline's starting point \"%s\"",
					 PQgetvalue(res, 0, 1));
		return false;
	}
	*startpos = ((uint64) startpos_xlogid << 32) | startpos_xrecoff;

	return true;
}