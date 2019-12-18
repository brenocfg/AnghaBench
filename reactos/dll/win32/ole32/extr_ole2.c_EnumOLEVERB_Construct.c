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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IEnumOLEVERB_iface; int /*<<< orphan*/  hkeyVerb; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ IEnumOLEVERB ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_2__ EnumOLEVERB ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumOLEVERB_VTable ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT EnumOLEVERB_Construct(HKEY hkeyVerb, ULONG index, IEnumOLEVERB **ppenum)
{
    EnumOLEVERB *This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This)
    {
        RegCloseKey(hkeyVerb);
        return E_OUTOFMEMORY;
    }
    This->IEnumOLEVERB_iface.lpVtbl = &EnumOLEVERB_VTable;
    This->ref = 1;
    This->index = index;
    This->hkeyVerb = hkeyVerb;
    *ppenum = &This->IEnumOLEVERB_iface;
    return S_OK;
}