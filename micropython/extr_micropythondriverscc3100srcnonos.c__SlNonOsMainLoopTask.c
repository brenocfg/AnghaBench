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
typedef  size_t _i8 ;
typedef  int /*<<< orphan*/  (* _SlSpawnEntryFunc_t ) (int /*<<< orphan*/ ) ;
struct TYPE_4__ {int /*<<< orphan*/ * pValue; int /*<<< orphan*/  (* pEntry ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ _SlNonOsSpawnEntry_t ;
typedef  int /*<<< orphan*/  _SlNonOsRetVal_t ;
struct TYPE_6__ {TYPE_1__* SpawnEntries; } ;
struct TYPE_5__ {scalar_t__ RxDoneCnt; } ;

/* Variables and functions */
 size_t NONOS_MAX_SPAWN_ENTRIES ; 
 int /*<<< orphan*/  NONOS_RET_OK ; 
 scalar_t__ RxIrqCnt ; 
 TYPE_3__ g__SlNonOsCB ; 
 TYPE_2__* g_pCB ; 

_SlNonOsRetVal_t _SlNonOsMainLoopTask(void)
{
	_i8 i=0;


#ifndef SL_TINY_EXT
	for (i=0 ; i<NONOS_MAX_SPAWN_ENTRIES ; i++)
#endif
	{
		_SlNonOsSpawnEntry_t* pE = &g__SlNonOsCB.SpawnEntries[i];
		_SlSpawnEntryFunc_t 		pF = pE->pEntry;
		
		if (NULL != pF)
		{
            if(RxIrqCnt != (g_pCB)->RxDoneCnt)
            {
                pF(0); /* (pValue) */
            }
            
			pE->pEntry = NULL;
			pE->pValue = NULL;
		}
	}
        
        return NONOS_RET_OK;
}