#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pipeRevWrite; int /*<<< orphan*/  pipeRevRead; TYPE_1__* AH; } ;
struct TYPE_6__ {int /*<<< orphan*/ * AHX; scalar_t__ pstate; } ;
struct TYPE_5__ {int /*<<< orphan*/  public; } ;
typedef  TYPE_2__ ShutdownInformation ;
typedef  TYPE_3__ ParallelSlot ;

/* Variables and functions */
 int /*<<< orphan*/  DisconnectDatabase (int /*<<< orphan*/ *) ; 
 TYPE_3__* GetMyPSlot (scalar_t__) ; 
 int /*<<< orphan*/  ShutdownWorkersHard (scalar_t__) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
archive_close_connection(int code, void *arg)
{
	ShutdownInformation *si = (ShutdownInformation *) arg;

	if (si->pstate)
	{
		/* In parallel mode, must figure out who we are */
		ParallelSlot *slot = GetMyPSlot(si->pstate);

		if (!slot)
		{
			/*
			 * We're the master.  Forcibly shut down workers, then close our
			 * own database connection, if any.
			 */
			ShutdownWorkersHard(si->pstate);

			if (si->AHX)
				DisconnectDatabase(si->AHX);
		}
		else
		{
			/*
			 * We're a worker.  Shut down our own DB connection if any.  On
			 * Windows, we also have to close our communication sockets, to
			 * emulate what will happen on Unix when the worker process exits.
			 * (Without this, if this is a premature exit, the master would
			 * fail to detect it because there would be no EOF condition on
			 * the other end of the pipe.)
			 */
			if (slot->AH)
				DisconnectDatabase(&(slot->AH->public));

#ifdef WIN32
			closesocket(slot->pipeRevRead);
			closesocket(slot->pipeRevWrite);
#endif
		}
	}
	else
	{
		/* Non-parallel operation: just kill the master DB connection */
		if (si->AHX)
			DisconnectDatabase(si->AHX);
	}
}