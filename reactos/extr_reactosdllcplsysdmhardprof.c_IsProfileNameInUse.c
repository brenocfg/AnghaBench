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
struct TYPE_7__ {int /*<<< orphan*/  szDestinationName; TYPE_2__* pProfileData; } ;
struct TYPE_6__ {size_t dwProfileCount; size_t dwSelectedProfileIndex; TYPE_1__* pProfiles; } ;
struct TYPE_5__ {int /*<<< orphan*/  szFriendlyName; } ;
typedef  TYPE_3__* PPROFILENAMES ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL
IsProfileNameInUse(
    PPROFILENAMES pProfileNames,
    BOOL bIgnoreCurrent)
{
    DWORD i;

    for (i = 0; i < pProfileNames->pProfileData->dwProfileCount; i++)
    {
        if (bIgnoreCurrent == TRUE && i == pProfileNames->pProfileData->dwSelectedProfileIndex)
            continue;

        if (wcscmp(pProfileNames->pProfileData->pProfiles[i].szFriendlyName, pProfileNames->szDestinationName) == 0)
            return TRUE;
    }

    return FALSE;
}