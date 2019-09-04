#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {struct TYPE_6__* szPagingFiles; TYPE_1__* Pagefile; } ;
struct TYPE_5__ {TYPE_2__* pszVolume; } ;
typedef  TYPE_2__* PVIRTMEM ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static VOID
OnDestroy(PVIRTMEM pVirtMem)
{
    INT i;

    for (i = 0; i < 26; i++)
    {
        if (pVirtMem->Pagefile[i].pszVolume != NULL)
            HeapFree(GetProcessHeap(), 0, pVirtMem->Pagefile[i].pszVolume);
    }

    if (pVirtMem->szPagingFiles)
        HeapFree(GetProcessHeap(), 0, pVirtMem->szPagingFiles);

    HeapFree(GetProcessHeap(), 0, pVirtMem);
}