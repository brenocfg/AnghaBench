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
struct TYPE_5__ {int ref; TYPE_1__ IUPnPNAT_iface; } ;
typedef  TYPE_2__ upnpnat ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  upnpnat_vtbl ; 

HRESULT IUPnPNAT_create(IUnknown *outer, void **object)
{
    upnpnat *nat;

    TRACE("(%p,%p)\n", outer, object);

    nat = heap_alloc( sizeof(*nat) );
    if (!nat) return E_OUTOFMEMORY;

    nat->IUPnPNAT_iface.lpVtbl = &upnpnat_vtbl;
    nat->ref = 1;

    *object = &nat->IUPnPNAT_iface;

    TRACE("returning iface %p\n", *object);
    return S_OK;
}