#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hDirectDrawLocal; } ;
struct TYPE_4__ {TYPE_3__* pUnknown6BC; } ;
typedef  TYPE_1__* LPD3D9_DEVICEDATA ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  OsThunkDdDeleteDirectDrawObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_NumDevices ; 

__attribute__((used)) static void ReleaseInternalDeviceData(LPD3D9_DEVICEDATA pDeviceData)
{
    OsThunkDdDeleteDirectDrawObject(pDeviceData->pUnknown6BC->hDirectDrawLocal);

    HeapFree(GetProcessHeap(), 0, pDeviceData->pUnknown6BC);
    pDeviceData->pUnknown6BC = NULL;

    --g_NumDevices;
}