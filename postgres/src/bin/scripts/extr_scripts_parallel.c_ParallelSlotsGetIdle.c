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
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int isFree; int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ ParallelSlot ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQconsumeInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQisBusy (int /*<<< orphan*/ ) ; 
 int PQsocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consumeQueryResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processQueryResult (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int select_loop (int,int /*<<< orphan*/ *,int*) ; 

ParallelSlot *
ParallelSlotsGetIdle(ParallelSlot *slots, int numslots)
{
	int			i;
	int			firstFree = -1;

	/*
	 * Look for any connection currently free.  If there is one, mark it as
	 * taken and let the caller know the slot to use.
	 */
	for (i = 0; i < numslots; i++)
	{
		if (slots[i].isFree)
		{
			slots[i].isFree = false;
			return slots + i;
		}
	}

	/*
	 * No free slot found, so wait until one of the connections has finished
	 * its task and return the available slot.
	 */
	while (firstFree < 0)
	{
		fd_set		slotset;
		int			maxFd = 0;
		bool		aborting;

		/* We must reconstruct the fd_set for each call to select_loop */
		FD_ZERO(&slotset);

		for (i = 0; i < numslots; i++)
		{
			int			sock = PQsocket(slots[i].connection);

			/*
			 * We don't really expect any connections to lose their sockets
			 * after startup, but just in case, cope by ignoring them.
			 */
			if (sock < 0)
				continue;

			FD_SET(sock, &slotset);
			if (sock > maxFd)
				maxFd = sock;
		}

		SetCancelConn(slots->connection);
		i = select_loop(maxFd, &slotset, &aborting);
		ResetCancelConn();

		if (aborting)
		{
			/*
			 * We set the cancel-receiving connection to the one in the zeroth
			 * slot above, so fetch the error from there.
			 */
			consumeQueryResult(slots->connection);
			return NULL;
		}
		Assert(i != 0);

		for (i = 0; i < numslots; i++)
		{
			int			sock = PQsocket(slots[i].connection);

			if (sock >= 0 && FD_ISSET(sock, &slotset))
			{
				/* select() says input is available, so consume it */
				PQconsumeInput(slots[i].connection);
			}

			/* Collect result(s) as long as any are available */
			while (!PQisBusy(slots[i].connection))
			{
				PGresult   *result = PQgetResult(slots[i].connection);

				if (result != NULL)
				{
					/* Check and discard the command result */
					if (!processQueryResult(slots[i].connection, result))
						return NULL;
				}
				else
				{
					/* This connection has become idle */
					slots[i].isFree = true;
					if (firstFree < 0)
						firstFree = i;
					break;
				}
			}
		}
	}

	slots[firstFree].isFree = false;
	return slots + firstFree;
}