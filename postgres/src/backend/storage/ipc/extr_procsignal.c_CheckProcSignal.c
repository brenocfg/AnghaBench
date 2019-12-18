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
struct TYPE_3__ {int* pss_signalFlags; } ;
typedef  TYPE_1__ ProcSignalSlot ;
typedef  size_t ProcSignalReason ;

/* Variables and functions */
 TYPE_1__* MyProcSignalSlot ; 

__attribute__((used)) static bool
CheckProcSignal(ProcSignalReason reason)
{
	volatile ProcSignalSlot *slot = MyProcSignalSlot;

	if (slot != NULL)
	{
		/* Careful here --- don't clear flag if we haven't seen it set */
		if (slot->pss_signalFlags[reason])
		{
			slot->pss_signalFlags[reason] = false;
			return true;
		}
	}

	return false;
}