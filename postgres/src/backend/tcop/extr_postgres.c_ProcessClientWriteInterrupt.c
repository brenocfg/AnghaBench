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

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ CritSectionCount ; 
 scalar_t__ DestNone ; 
 scalar_t__ DestRemote ; 
 scalar_t__ InterruptHoldoffCount ; 
 int /*<<< orphan*/  MyLatch ; 
 scalar_t__ ProcDiePending ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ whereToSendOutput ; 

void
ProcessClientWriteInterrupt(bool blocked)
{
	int			save_errno = errno;

	if (ProcDiePending)
	{
		/*
		 * We're dying.  If it's not possible to write, then we should handle
		 * that immediately, else a stuck client could indefinitely delay our
		 * response to the signal.  If we haven't tried to write yet, make
		 * sure the process latch is set, so that if the write would block
		 * then we'll come back here and die.  If we're done writing, also
		 * make sure the process latch is set, as we might've undesirably
		 * cleared it while writing.
		 */
		if (blocked)
		{
			/*
			 * Don't mess with whereToSendOutput if ProcessInterrupts wouldn't
			 * do anything.
			 */
			if (InterruptHoldoffCount == 0 && CritSectionCount == 0)
			{
				/*
				 * We don't want to send the client the error message, as a)
				 * that would possibly block again, and b) it would likely
				 * lead to loss of protocol sync because we may have already
				 * sent a partial protocol message.
				 */
				if (whereToSendOutput == DestRemote)
					whereToSendOutput = DestNone;

				CHECK_FOR_INTERRUPTS();
			}
		}
		else
			SetLatch(MyLatch);
	}

	errno = save_errno;
}