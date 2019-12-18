#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int ref; TYPE_5__ IBindStatusCallbackEx_iface; TYPE_4__ IAuthenticate_iface; TYPE_3__ IHttpNegotiate2_iface; TYPE_2__ IServiceProvider_iface; TYPE_1__ IInternetBindInfo_iface; } ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_6__ BindStatusCallback ;

/* Variables and functions */
 int /*<<< orphan*/  BSCAuthenticateVtbl ; 
 int /*<<< orphan*/  BSCHttpNegotiateVtbl ; 
 int /*<<< orphan*/  BSCInternetBindInfoVtbl ; 
 int /*<<< orphan*/  BSCServiceProviderVtbl ; 
 int /*<<< orphan*/  BindStatusCallbackExVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_6__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  set_callback (TYPE_6__*,int /*<<< orphan*/ *) ; 

HRESULT wrap_callback(IBindStatusCallback *bsc, IBindStatusCallback **ret_iface)
{
    BindStatusCallback *ret;

    ret = heap_alloc_zero(sizeof(BindStatusCallback));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IBindStatusCallbackEx_iface.lpVtbl = &BindStatusCallbackExVtbl;
    ret->IInternetBindInfo_iface.lpVtbl = &BSCInternetBindInfoVtbl;
    ret->IServiceProvider_iface.lpVtbl = &BSCServiceProviderVtbl;
    ret->IHttpNegotiate2_iface.lpVtbl = &BSCHttpNegotiateVtbl;
    ret->IAuthenticate_iface.lpVtbl = &BSCAuthenticateVtbl;

    ret->ref = 1;
    set_callback(ret, bsc);

    *ret_iface = (IBindStatusCallback*)&ret->IBindStatusCallbackEx_iface;
    return S_OK;
}