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
typedef  int /*<<< orphan*/ * P_EVENT_HANDLER ;

/* Variables and functions */
 int /*<<< orphan*/  INT_NWPIC ; 
 int /*<<< orphan*/  INT_PRIORITY_LVL_1 ; 
 int /*<<< orphan*/  MAP_IntDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntPendClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntPrioritySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_IntRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAP_IntUnregister (int /*<<< orphan*/ ) ; 

int NwpRegisterInterruptHandler(P_EVENT_HANDLER InterruptHdl , void* pValue)
{

    if(InterruptHdl == NULL)
    {
		//De-register Interprocessor communication interrupt between App and NWP
		#ifdef SL_PLATFORM_MULTI_THREADED
		  osi_InterruptDeRegister(INT_NWPIC);
		#else
		  MAP_IntDisable(INT_NWPIC);
		  MAP_IntUnregister(INT_NWPIC);
		  MAP_IntPendClear(INT_NWPIC);
		#endif
    }
    else
    {
		  #ifdef SL_PLATFORM_MULTI_THREADED
			 MAP_IntPendClear(INT_NWPIC);
			 osi_InterruptRegister(INT_NWPIC, (P_OSI_INTR_ENTRY)InterruptHdl,INT_PRIORITY_LVL_1);
		  #else
			 MAP_IntRegister(INT_NWPIC, InterruptHdl);
			 MAP_IntPrioritySet(INT_NWPIC, INT_PRIORITY_LVL_1);
			 MAP_IntPendClear(INT_NWPIC);
			 MAP_IntEnable(INT_NWPIC);
		  #endif
    }

  return 0;
}