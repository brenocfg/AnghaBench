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
typedef  size_t _u8 ;
struct TYPE_4__ {TYPE_1__* ObjPool; } ;
struct TYPE_3__ {size_t NextIndex; } ;

/* Variables and functions */
 size_t MAX_CONCURRENT_ACTIONS ; 
 TYPE_2__* g_pCB ; 

void _SlRemoveFromList(_u8 *ListIndex, _u8 ItemIndex)
{
#ifndef SL_TINY_EXT  
	_u8 Idx;
#endif        
        
    if (MAX_CONCURRENT_ACTIONS == g_pCB->ObjPool[*ListIndex].NextIndex)
    {
        *ListIndex = MAX_CONCURRENT_ACTIONS;
    }
    /* As MAX_CONCURRENT_ACTIONS is equal to 1 in Tiny mode */
#ifndef SL_TINY_EXT
	/* need to remove the first item in the list and therefore update the global which holds this index */
	else if (*ListIndex == ItemIndex)
	{
		*ListIndex = g_pCB->ObjPool[ItemIndex].NextIndex;
	}
	else
	{
              Idx = *ListIndex;
      
              while(MAX_CONCURRENT_ACTIONS > Idx)
              {
                  /* remove from list */
                  if (g_pCB->ObjPool[Idx].NextIndex == ItemIndex)
                  {
                          g_pCB->ObjPool[Idx].NextIndex = g_pCB->ObjPool[ItemIndex].NextIndex;
                          break;
                  }

                  Idx = g_pCB->ObjPool[Idx].NextIndex;
              }
	}
#endif    
}