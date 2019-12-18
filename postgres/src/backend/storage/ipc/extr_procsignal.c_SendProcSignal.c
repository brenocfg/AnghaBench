#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {scalar_t__ pss_pid; int* pss_signalFlags; } ;
typedef  TYPE_1__ ProcSignalSlot ;
typedef  size_t ProcSignalReason ;
typedef  int BackendId ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 int InvalidBackendId ; 
 int NumProcSignalSlots ; 
 TYPE_1__* ProcSignalSlots ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  errno ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 

int
SendProcSignal(pid_t pid, ProcSignalReason reason, BackendId backendId)
{
	volatile ProcSignalSlot *slot;

	if (backendId != InvalidBackendId)
	{
		slot = &ProcSignalSlots[backendId - 1];

		/*
		 * Note: Since there's no locking, it's possible that the target
		 * process detaches from shared memory and exits right after this
		 * test, before we set the flag and send signal. And the signal slot
		 * might even be recycled by a new process, so it's remotely possible
		 * that we set a flag for a wrong process. That's OK, all the signals
		 * are such that no harm is done if they're mistakenly fired.
		 */
		if (slot->pss_pid == pid)
		{
			/* Atomically set the proper flag */
			slot->pss_signalFlags[reason] = true;
			/* Send signal */
			return kill(pid, SIGUSR1);
		}
	}
	else
	{
		/*
		 * BackendId not provided, so search the array using pid.  We search
		 * the array back to front so as to reduce search overhead.  Passing
		 * InvalidBackendId means that the target is most likely an auxiliary
		 * process, which will have a slot near the end of the array.
		 */
		int			i;

		for (i = NumProcSignalSlots - 1; i >= 0; i--)
		{
			slot = &ProcSignalSlots[i];

			if (slot->pss_pid == pid)
			{
				/* the above note about race conditions applies here too */

				/* Atomically set the proper flag */
				slot->pss_signalFlags[reason] = true;
				/* Send signal */
				return kill(pid, SIGUSR1);
			}
		}
	}

	errno = ESRCH;
	return -1;
}