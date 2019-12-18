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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {void* propName; } ;
typedef  TYPE_1__ IDxDiagContainerImpl_Property ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  lstrcpyW (void*,int /*<<< orphan*/  const*) ; 
 int lstrlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static IDxDiagContainerImpl_Property *allocate_property_information(const WCHAR *name)
{
    IDxDiagContainerImpl_Property *ret;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        return NULL;

    ret->propName = HeapAlloc(GetProcessHeap(), 0, (lstrlenW(name) + 1) * sizeof(*name));
    if (!ret->propName)
    {
        HeapFree(GetProcessHeap(), 0, ret);
        return NULL;
    }
    lstrcpyW(ret->propName, name);

    return ret;
}