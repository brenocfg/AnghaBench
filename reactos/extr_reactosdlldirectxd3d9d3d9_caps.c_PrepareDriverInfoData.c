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
struct TYPE_4__ {int dwSize; int /*<<< orphan*/  ddRVal; int /*<<< orphan*/  lpvData; int /*<<< orphan*/  dwExpectedSize; int /*<<< orphan*/  guidInfo; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DD_GETDRIVERINFODATA ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GUID_GetDriverInfo2 ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PrepareDriverInfoData(DD_GETDRIVERINFODATA* DrvInfo, LPVOID pData, DWORD dwExpectedSize)
{
    memset(DrvInfo, 0, sizeof(DD_GETDRIVERINFODATA));
    DrvInfo->dwSize = sizeof(DD_GETDRIVERINFODATA);
    DrvInfo->guidInfo = GUID_GetDriverInfo2;
    DrvInfo->dwExpectedSize = dwExpectedSize;
    DrvInfo->lpvData = pData;
    DrvInfo->ddRVal = E_FAIL;
}