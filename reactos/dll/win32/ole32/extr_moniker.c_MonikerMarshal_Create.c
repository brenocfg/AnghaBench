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
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_3__ IUnknown_iface; int /*<<< orphan*/ * moniker; TYPE_1__ IMarshal_iface; } ;
typedef  TYPE_2__ MonikerMarshal ;
typedef  TYPE_3__ IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VT_MonikerMarshal ; 
 int /*<<< orphan*/  VT_MonikerMarshalInner ; 

HRESULT MonikerMarshal_Create(IMoniker *inner, IUnknown **outer)
{
    MonikerMarshal *This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IUnknown_iface.lpVtbl = &VT_MonikerMarshalInner;
    This->IMarshal_iface.lpVtbl = &VT_MonikerMarshal;
    This->ref = 1;
    This->moniker = inner;

    *outer = &This->IUnknown_iface;
    return S_OK;
}