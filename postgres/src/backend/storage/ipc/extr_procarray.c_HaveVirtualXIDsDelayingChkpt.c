#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VirtualTransactionId ;
struct TYPE_6__ {scalar_t__ delayChkpt; } ;
struct TYPE_5__ {int numProcs; int* pgprocnos; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGXACT ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  GET_VXID_FROM_PGPROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 scalar_t__ VirtualTransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VirtualTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 TYPE_2__* allPgXact ; 
 int /*<<< orphan*/ * allProcs ; 
 TYPE_1__* procArray ; 

bool
HaveVirtualXIDsDelayingChkpt(VirtualTransactionId *vxids, int nvxids)
{
	bool		result = false;
	ProcArrayStruct *arrayP = procArray;
	int			index;

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		PGPROC	   *proc = &allProcs[pgprocno];
		PGXACT	   *pgxact = &allPgXact[pgprocno];
		VirtualTransactionId vxid;

		GET_VXID_FROM_PGPROC(vxid, *proc);

		if (pgxact->delayChkpt && VirtualTransactionIdIsValid(vxid))
		{
			int			i;

			for (i = 0; i < nvxids; i++)
			{
				if (VirtualTransactionIdEquals(vxid, vxids[i]))
				{
					result = true;
					break;
				}
			}
			if (result)
				break;
		}
	}

	LWLockRelease(ProcArrayLock);

	return result;
}