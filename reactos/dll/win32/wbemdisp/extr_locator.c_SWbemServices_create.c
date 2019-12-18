#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct services {int refs; TYPE_1__ ISWbemServices_iface; int /*<<< orphan*/ * services; } ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  TYPE_1__ ISWbemServices ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IWbemServices_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 struct services* heap_alloc (int) ; 
 int /*<<< orphan*/  services_vtbl ; 

__attribute__((used)) static HRESULT SWbemServices_create( IWbemServices *wbem_services, ISWbemServices **obj )
{
    struct services *services;

    TRACE( "%p, %p\n", obj, wbem_services );

    if (!(services = heap_alloc( sizeof(*services) ))) return E_OUTOFMEMORY;
    services->ISWbemServices_iface.lpVtbl = &services_vtbl;
    services->refs = 1;
    services->services = wbem_services;
    IWbemServices_AddRef( services->services );

    *obj = &services->ISWbemServices_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}