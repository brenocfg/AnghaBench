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
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_11__ {int ref; TYPE_3__ IInternetProtocol_iface; TYPE_1__ IInternetPriority_iface; TYPE_2__ base; } ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ GopherProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  AsyncProtocolVtbl ; 
 int /*<<< orphan*/  GopherPriorityVtbl ; 
 int /*<<< orphan*/  GopherProtocolVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 TYPE_4__* heap_alloc_zero (int) ; 

HRESULT GopherProtocol_Construct(IUnknown *pUnkOuter, LPVOID *ppobj)
{
    GopherProtocol *ret;

    TRACE("(%p %p)\n", pUnkOuter, ppobj);

    URLMON_LockModule();

    ret = heap_alloc_zero(sizeof(GopherProtocol));

    ret->base.vtbl = &AsyncProtocolVtbl;
    ret->IInternetProtocol_iface.lpVtbl = &GopherProtocolVtbl;
    ret->IInternetPriority_iface.lpVtbl = &GopherPriorityVtbl;
    ret->ref = 1;

    *ppobj = &ret->IInternetProtocol_iface;

    return S_OK;
}