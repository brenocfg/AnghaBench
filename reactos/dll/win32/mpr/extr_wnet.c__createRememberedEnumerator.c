#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WNetEnumerator ;
struct TYPE_6__ {int /*<<< orphan*/  registry; } ;
struct TYPE_7__ {TYPE_1__ remembered; } ;
struct TYPE_8__ {TYPE_2__ specific; void* dwType; void* dwScope; int /*<<< orphan*/  enumType; } ;
typedef  TYPE_3__* PWNetEnumerator ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WNET_ENUMERATOR_TYPE_REMEMBERED ; 

__attribute__((used)) static PWNetEnumerator _createRememberedEnumerator(DWORD dwScope, DWORD dwType,
 HKEY remembered)
{
    PWNetEnumerator ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WNetEnumerator));
    if (ret)
    {
        ret->enumType = WNET_ENUMERATOR_TYPE_REMEMBERED;
        ret->dwScope = dwScope;
        ret->dwType = dwType;
        ret->specific.remembered.registry = remembered;
    }
    return ret;
}