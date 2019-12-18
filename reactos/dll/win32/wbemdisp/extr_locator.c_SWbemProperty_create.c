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
struct property {int refs; TYPE_1__ ISWbemProperty_iface; int /*<<< orphan*/  name; int /*<<< orphan*/ * object; } ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  TYPE_1__ ISWbemProperty ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocStringLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 struct property* heap_alloc (int) ; 
 int /*<<< orphan*/  property_vtbl ; 

__attribute__((used)) static HRESULT SWbemProperty_create( IWbemClassObject *wbem_object, BSTR name, ISWbemProperty **obj )
{
    struct property *property;

    TRACE( "%p, %p\n", obj, wbem_object );

    if (!(property = heap_alloc( sizeof(*property) ))) return E_OUTOFMEMORY;
    property->ISWbemProperty_iface.lpVtbl = &property_vtbl;
    property->refs = 1;
    property->object = wbem_object;
    IWbemClassObject_AddRef( property->object );
    property->name = SysAllocStringLen( name, SysStringLen( name ) );
    *obj = &property->ISWbemProperty_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}