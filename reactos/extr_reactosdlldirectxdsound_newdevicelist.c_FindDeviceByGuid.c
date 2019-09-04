#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* lpNext; int /*<<< orphan*/ * DeviceGuid; } ;
typedef  TYPE_1__* LPFILTERINFO ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* RootInfo ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
FindDeviceByGuid(
    LPCGUID pGuidSrc, 
    LPFILTERINFO *Filter)
{
    LPFILTERINFO CurInfo;
    if (!RootInfo)
        return FALSE;

    /* get first entry */
    CurInfo = RootInfo;

    while(CurInfo)
    {
        if (IsEqualGUID(&CurInfo->DeviceGuid[0], pGuidSrc) ||
            IsEqualGUID(&CurInfo->DeviceGuid[1], pGuidSrc))
        {
            /* found filter */
            *Filter = CurInfo;
            return TRUE;
        }

        CurInfo = CurInfo->lpNext;
    }

    return FALSE;
}