#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hModule; struct TYPE_5__* lpNextItem; } ;
typedef  TYPE_1__ WINE_DRIVER ;
typedef  TYPE_1__* LPWINE_DRIVER ;
typedef  scalar_t__ HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 TYPE_1__* lpDrvItemList ; 
 int /*<<< orphan*/  mmdriver_lock ; 

__attribute__((used)) static	unsigned DRIVER_GetNumberOfModuleRefs(HMODULE hModule, WINE_DRIVER** found)
{
    LPWINE_DRIVER	lpDrv;
    unsigned		count = 0;

    EnterCriticalSection( &mmdriver_lock );

    if (found) *found = NULL;
    for (lpDrv = lpDrvItemList; lpDrv; lpDrv = lpDrv->lpNextItem)
    {
	if (lpDrv->hModule == hModule)
        {
            if (found && !*found) *found = lpDrv;
	    count++;
	}
    }

    LeaveCriticalSection( &mmdriver_lock );
    return count;
}