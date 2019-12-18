#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; int /*<<< orphan*/ * mon; int /*<<< orphan*/  entry; int /*<<< orphan*/  bom; int /*<<< orphan*/  bindf; int /*<<< orphan*/  const* vtbl; TYPE_3__ IInternetBindInfo_iface; TYPE_2__ IHttpNegotiate2_iface; TYPE_1__ IServiceProvider_iface; TYPE_4__ IBindStatusCallback_iface; } ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSCallbackVtbl ;
typedef  TYPE_5__ BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  BOM_NONE ; 
 int /*<<< orphan*/  BindStatusCallbackVtbl ; 
 int /*<<< orphan*/  HttpNegotiate2Vtbl ; 
 int /*<<< orphan*/  IMoniker_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetBindInfoVtbl ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

void init_bscallback(BSCallback *This, const BSCallbackVtbl *vtbl, IMoniker *mon, DWORD bindf)
{
    This->IBindStatusCallback_iface.lpVtbl = &BindStatusCallbackVtbl;
    This->IServiceProvider_iface.lpVtbl = &ServiceProviderVtbl;
    This->IHttpNegotiate2_iface.lpVtbl = &HttpNegotiate2Vtbl;
    This->IInternetBindInfo_iface.lpVtbl = &InternetBindInfoVtbl;
    This->vtbl = vtbl;
    This->ref = 1;
    This->bindf = bindf;
    This->bom = BOM_NONE;

    list_init(&This->entry);

    if(mon)
        IMoniker_AddRef(mon);
    This->mon = mon;
}