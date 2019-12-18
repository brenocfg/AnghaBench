#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* freeProcs; } ;
struct TYPE_4__ {scalar_t__ next; } ;
struct TYPE_5__ {TYPE_1__ links; } ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 TYPE_3__* ProcGlobal ; 
 int /*<<< orphan*/  ProcStructLock ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ ) ; 

bool
HaveNFreeProcs(int n)
{
	PGPROC	   *proc;

	SpinLockAcquire(ProcStructLock);

	proc = ProcGlobal->freeProcs;

	while (n > 0 && proc != NULL)
	{
		proc = (PGPROC *) proc->links.next;
		n--;
	}

	SpinLockRelease(ProcStructLock);

	return (n <= 0);
}