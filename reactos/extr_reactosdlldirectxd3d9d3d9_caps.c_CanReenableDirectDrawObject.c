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
struct TYPE_3__ {scalar_t__ DeviceType; int /*<<< orphan*/  hDirectDrawLocal; } ;
typedef  TYPE_1__ D3D9_Unknown6BC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ D3DDEVTYPE_REF ; 
 scalar_t__ D3DDEVTYPE_SW ; 
 scalar_t__ FALSE ; 
 scalar_t__ OsThunkDdReenableDirectDrawObject (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ TRUE ; 

BOOL CanReenableDirectDrawObject(D3D9_Unknown6BC* pUnknown)
{
    BOOL bDisplayModeWasChanged;

    /* Try the real way first */
    if (TRUE == OsThunkDdReenableDirectDrawObject(pUnknown->hDirectDrawLocal, &bDisplayModeWasChanged))
        return TRUE;

    /* Ref types and software types can always be reenabled after a mode switch */
    if (pUnknown->DeviceType == D3DDEVTYPE_REF || pUnknown->DeviceType == D3DDEVTYPE_SW)
        return TRUE;

    return FALSE;
}