#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct locator {int refs; TYPE_1__ ISWbemLocator_iface; int /*<<< orphan*/ * locator; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 struct locator* heap_alloc (int) ; 
 int /*<<< orphan*/  locator_vtbl ; 

HRESULT SWbemLocator_create( void **obj )
{
    struct locator *locator;

    TRACE( "%p\n", obj );

    if (!(locator = heap_alloc( sizeof(*locator) ))) return E_OUTOFMEMORY;
    locator->ISWbemLocator_iface.lpVtbl = &locator_vtbl;
    locator->refs = 1;
    locator->locator = NULL;

    *obj = &locator->ISWbemLocator_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}