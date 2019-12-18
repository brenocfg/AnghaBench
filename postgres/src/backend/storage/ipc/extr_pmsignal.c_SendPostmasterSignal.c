#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* PMSignalFlags; } ;
typedef  size_t PMSignalReason ;

/* Variables and functions */
 int /*<<< orphan*/  IsUnderPostmaster ; 
 TYPE_1__* PMSignalState ; 
 int /*<<< orphan*/  PostmasterPid ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
SendPostmasterSignal(PMSignalReason reason)
{
	/* If called in a standalone backend, do nothing */
	if (!IsUnderPostmaster)
		return;
	/* Atomically set the proper flag */
	PMSignalState->PMSignalFlags[reason] = true;
	/* Send signal to postmaster */
	kill(PostmasterPid, SIGUSR1);
}