#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pid; } ;
struct TYPE_6__ {int numProcs; size_t* pgprocnos; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 TYPE_2__* allProcs ; 
 TYPE_1__* procArray ; 

PGPROC *
BackendPidGetProcWithLock(int pid)
{
	PGPROC	   *result = NULL;
	ProcArrayStruct *arrayP = procArray;
	int			index;

	if (pid == 0)				/* never match dummy PGPROCs */
		return NULL;

	for (index = 0; index < arrayP->numProcs; index++)
	{
		PGPROC	   *proc = &allProcs[arrayP->pgprocnos[index]];

		if (proc->pid == pid)
		{
			result = proc;
			break;
		}
	}

	return result;
}