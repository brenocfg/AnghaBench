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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_1__ IMetaDataDispenserEx_iface; } ;
typedef  TYPE_2__ MetaDataDispenser ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MetaDataDispenserVtbl ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT MetaDataDispenser_CreateInstance(IUnknown **ppUnk)
{
    MetaDataDispenser *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(MetaDataDispenser));

    if (!This)
        return E_OUTOFMEMORY;

    This->IMetaDataDispenserEx_iface.lpVtbl = &MetaDataDispenserVtbl;
    This->ref = 1;

    *ppUnk = (IUnknown*)This;

    return S_OK;
}