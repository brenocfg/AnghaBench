#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {struct TYPE_5__* lpDisplayName; struct TYPE_5__* lpServiceName; } ;
struct TYPE_4__ {size_t NumServices; TYPE_2__* pAllServices; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessHeap ; 

VOID
FreeServiceList(PMAIN_WND_INFO Info)
{
    DWORD i;

    if (Info->pAllServices != NULL)
    {
        for (i = 0; i < Info->NumServices; i++)
        {
            if (Info->pAllServices[i].lpServiceName)
                HeapFree(ProcessHeap, 0, Info->pAllServices[i].lpServiceName);

            if (Info->pAllServices[i].lpDisplayName)
                HeapFree(ProcessHeap, 0, Info->pAllServices[i].lpDisplayName);
        }

        HeapFree(ProcessHeap, 0, Info->pAllServices);
        Info->pAllServices = NULL;
        Info->NumServices = 0;
    }
}