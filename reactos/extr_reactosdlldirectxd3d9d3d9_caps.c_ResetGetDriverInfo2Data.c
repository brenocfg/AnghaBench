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
struct TYPE_4__ {void* dwExpectedSize; void* dwType; int /*<<< orphan*/  dwMagic; } ;
typedef  void* DWORD ;
typedef  TYPE_1__ DD_GETDRIVERINFO2DATA ;

/* Variables and functions */
 int /*<<< orphan*/  D3DGDI2_MAGIC ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void ResetGetDriverInfo2Data(DD_GETDRIVERINFO2DATA* DrvInfo2, DWORD dwType, DWORD dwExpectedSize)
{
    memset(DrvInfo2, 0, dwExpectedSize);
    DrvInfo2->dwMagic = D3DGDI2_MAGIC;
    DrvInfo2->dwType = dwType;
    DrvInfo2->dwExpectedSize = dwExpectedSize;
}