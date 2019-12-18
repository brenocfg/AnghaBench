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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_2__ ICorDebug_iface; int /*<<< orphan*/ * runtimehost; int /*<<< orphan*/  processes; int /*<<< orphan*/ * pCallback2; int /*<<< orphan*/ * pCallback; TYPE_1__ ICorDebugProcessEnum_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ICLRRuntimeHost ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ CorDebug ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICLRRuntimeHost_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  cordebug_vtbl ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processenum_vtbl ; 

HRESULT CorDebug_Create(ICLRRuntimeHost *runtimehost, IUnknown** ppUnk)
{
    CorDebug *This;

    This = HeapAlloc( GetProcessHeap(), 0, sizeof *This );
    if ( !This )
        return E_OUTOFMEMORY;

    This->ICorDebug_iface.lpVtbl = &cordebug_vtbl;
    This->ICorDebugProcessEnum_iface.lpVtbl = &processenum_vtbl;
    This->ref = 1;
    This->pCallback = NULL;
    This->pCallback2 = NULL;
    This->runtimehost = runtimehost;

    list_init(&This->processes);

    if(This->runtimehost)
        ICLRRuntimeHost_AddRef(This->runtimehost);

    *ppUnk = (IUnknown*)&This->ICorDebug_iface;

    return S_OK;
}