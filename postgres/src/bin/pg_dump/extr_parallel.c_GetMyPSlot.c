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
struct TYPE_6__ {scalar_t__ threadId; scalar_t__ pid; } ;
struct TYPE_5__ {int numWorkers; TYPE_2__* parallelSlot; } ;
typedef  TYPE_1__ ParallelState ;
typedef  TYPE_2__ ParallelSlot ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 scalar_t__ getpid () ; 

__attribute__((used)) static ParallelSlot *
GetMyPSlot(ParallelState *pstate)
{
	int			i;

	for (i = 0; i < pstate->numWorkers; i++)
	{
#ifdef WIN32
		if (pstate->parallelSlot[i].threadId == GetCurrentThreadId())
#else
		if (pstate->parallelSlot[i].pid == getpid())
#endif
			return &(pstate->parallelSlot[i]);
	}

	return NULL;
}