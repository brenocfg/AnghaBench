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
typedef  int WFW_WaitOption ;
typedef  int /*<<< orphan*/  ParallelState ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetIdleWorker (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEveryWorkerIdle (int /*<<< orphan*/ *) ; 
 scalar_t__ ListenToWorkers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NO_SLOT ; 
#define  WFW_ALL_IDLE 131 
#define  WFW_GOT_STATUS 130 
#define  WFW_NO_WAIT 129 
#define  WFW_ONE_IDLE 128 

void
WaitForWorkers(ArchiveHandle *AH, ParallelState *pstate, WFW_WaitOption mode)
{
	bool		do_wait = false;

	/*
	 * In GOT_STATUS mode, always block waiting for a message, since we can't
	 * return till we get something.  In other modes, we don't block the first
	 * time through the loop.
	 */
	if (mode == WFW_GOT_STATUS)
	{
		/* Assert that caller knows what it's doing */
		Assert(!IsEveryWorkerIdle(pstate));
		do_wait = true;
	}

	for (;;)
	{
		/*
		 * Check for status messages, even if we don't need to block.  We do
		 * not try very hard to reap all available messages, though, since
		 * there's unlikely to be more than one.
		 */
		if (ListenToWorkers(AH, pstate, do_wait))
		{
			/*
			 * If we got a message, we are done by definition for GOT_STATUS
			 * mode, and we can also be certain that there's at least one idle
			 * worker.  So we're done in all but ALL_IDLE mode.
			 */
			if (mode != WFW_ALL_IDLE)
				return;
		}

		/* Check whether we must wait for new status messages */
		switch (mode)
		{
			case WFW_NO_WAIT:
				return;			/* never wait */
			case WFW_GOT_STATUS:
				Assert(false);	/* can't get here, because we waited */
				break;
			case WFW_ONE_IDLE:
				if (GetIdleWorker(pstate) != NO_SLOT)
					return;
				break;
			case WFW_ALL_IDLE:
				if (IsEveryWorkerIdle(pstate))
					return;
				break;
		}

		/* Loop back, and this time wait for something to happen */
		do_wait = true;
	}
}