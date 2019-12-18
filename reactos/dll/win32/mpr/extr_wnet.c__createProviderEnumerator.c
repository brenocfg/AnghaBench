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
typedef  int /*<<< orphan*/  WNetEnumerator ;
struct TYPE_6__ {scalar_t__ numProviders; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; scalar_t__ dwUsage; scalar_t__ dwType; scalar_t__ dwScope; scalar_t__ providerIndex; int /*<<< orphan*/  enumType; } ;
typedef  TYPE_1__* PWNetEnumerator ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WNET_ENUMERATOR_TYPE_PROVIDER ; 
 TYPE_2__* providerTable ; 

__attribute__((used)) static PWNetEnumerator _createProviderEnumerator(DWORD dwScope, DWORD dwType,
 DWORD dwUsage, DWORD index, HANDLE handle)
{
    PWNetEnumerator ret;

    if (!providerTable || index >= providerTable->numProviders)
        ret = NULL;
    else
    {
        ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WNetEnumerator));
        if (ret)
        {
            ret->enumType      = WNET_ENUMERATOR_TYPE_PROVIDER;
            ret->providerIndex = index;
            ret->dwScope       = dwScope;
            ret->dwType        = dwType;
            ret->dwUsage       = dwUsage;
            ret->handle        = handle;
        }
    }
    return ret;
}