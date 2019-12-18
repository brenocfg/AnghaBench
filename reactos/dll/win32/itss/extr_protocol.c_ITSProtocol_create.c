#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_3__ IUnknown_inner; TYPE_3__* outer; TYPE_2__ IInternetProtocolInfo_iface; TYPE_1__ IInternetProtocol_iface; } ;
typedef  TYPE_3__ IUnknown ;
typedef  TYPE_4__ ITSProtocol ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ITSProtocolInfoVtbl ; 
 int /*<<< orphan*/  ITSProtocolUnkVtbl ; 
 int /*<<< orphan*/  ITSProtocolVtbl ; 
 int /*<<< orphan*/  ITSS_LockModule () ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,void**) ; 

HRESULT ITSProtocol_create(IUnknown *outer, void **ppv)
{
    ITSProtocol *ret;

    TRACE("(%p %p)\n", outer, ppv);

    ITSS_LockModule();

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ITSProtocol));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IUnknown_inner.lpVtbl = &ITSProtocolUnkVtbl;
    ret->IInternetProtocol_iface.lpVtbl = &ITSProtocolVtbl;
    ret->IInternetProtocolInfo_iface.lpVtbl = &ITSProtocolInfoVtbl;
    ret->ref = 1;
    ret->outer = outer ? outer : &ret->IUnknown_inner;

    *ppv = &ret->IUnknown_inner;
    return S_OK;
}