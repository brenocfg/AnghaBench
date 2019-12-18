#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dwDriverID; } ;
struct TYPE_6__ {TYPE_1__ d32; } ;
struct TYPE_7__ {struct TYPE_7__* lpNextItem; TYPE_2__ d; int /*<<< orphan*/  dwMagic; } ;
typedef  TYPE_3__* LPWINE_DRIVER ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_3__* lpDrvItemList ; 
 int /*<<< orphan*/  mmdriver_lock ; 

__attribute__((used)) static void DRIVER_Dump(const char *comment)
{
#if 0
    LPWINE_DRIVER 	lpDrv;

    TRACE("%s\n", comment);

    EnterCriticalSection( &mmdriver_lock );

    for (lpDrv = lpDrvItemList; lpDrv != NULL; lpDrv = lpDrv->lpNextItem)
    {
        TRACE("%p, magic %04lx, id %p, next %p\n", lpDrv, lpDrv->dwMagic, lpDrv->d.d32.dwDriverID, lpDrv->lpNextItem);
    }

    LeaveCriticalSection( &mmdriver_lock );
#endif
}