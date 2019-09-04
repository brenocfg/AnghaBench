#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _u32 ;
typedef  size_t _i8 ;
typedef  int /*<<< orphan*/ * _SlSpawnEntryFunc_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pEntry; void* pValue; } ;
typedef  TYPE_1__ _SlNonOsSpawnEntry_t ;
typedef  int /*<<< orphan*/  _SlNonOsRetVal_t ;
struct TYPE_4__ {TYPE_1__* SpawnEntries; } ;

/* Variables and functions */
 size_t NONOS_MAX_SPAWN_ENTRIES ; 
 int /*<<< orphan*/  NONOS_RET_OK ; 
 TYPE_2__ g__SlNonOsCB ; 

_SlNonOsRetVal_t _SlNonOsSpawn(_SlSpawnEntryFunc_t pEntry , void* pValue , _u32 flags)
{
	 _i8 i = 0;
    
#ifndef SL_TINY_EXT 	
	for (i=0 ; i<NONOS_MAX_SPAWN_ENTRIES ; i++)
#endif     
	{
		_SlNonOsSpawnEntry_t* pE = &g__SlNonOsCB.SpawnEntries[i];
	
		if (NULL == pE->pEntry)
		{
			pE->pValue = pValue;
			pE->pEntry = pEntry;
#ifndef SL_TINY_EXT 	                        
			break;
#endif                        
		}
	}
        
        
        return NONOS_RET_OK;
}