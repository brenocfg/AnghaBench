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
typedef  int /*<<< orphan*/  ParallelSlot ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ FD_SETSIZE ; 
 scalar_t__ PQsocket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * connectDatabase (char const*,char const*,char const*,char const*,int,char const*,int,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  init_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_fatal (char*,int) ; 
 scalar_t__ pg_malloc (int) ; 

ParallelSlot *
ParallelSlotsSetup(const char *dbname, const char *host, const char *port,
				   const char *username, bool prompt_password,
				   const char *progname, bool echo,
				   PGconn *conn, int numslots)
{
	ParallelSlot *slots;
	int			i;

	Assert(conn != NULL);

	slots = (ParallelSlot *) pg_malloc(sizeof(ParallelSlot) * numslots);
	init_slot(slots, conn);
	if (numslots > 1)
	{
		for (i = 1; i < numslots; i++)
		{
			conn = connectDatabase(dbname, host, port, username, prompt_password,
								   progname, echo, false, true);

			/*
			 * Fail and exit immediately if trying to use a socket in an
			 * unsupported range.  POSIX requires open(2) to use the lowest
			 * unused file descriptor and the hint given relies on that.
			 */
			if (PQsocket(conn) >= FD_SETSIZE)
			{
				pg_log_fatal("too many jobs for this platform -- try %d", i);
				exit(1);
			}

			init_slot(slots + i, conn);
		}
	}

	return slots;
}