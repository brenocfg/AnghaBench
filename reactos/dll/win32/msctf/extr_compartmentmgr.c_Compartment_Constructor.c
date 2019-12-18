#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int refCount; TYPE_2__ ITfCompartment_iface; int /*<<< orphan*/  CompartmentEventSink; int /*<<< orphan*/  variant; int /*<<< orphan*/ * valueData; TYPE_1__ ITfSource_iface; } ;
typedef  TYPE_2__ ITfCompartment ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CompartmentValue ;
typedef  TYPE_3__ Compartment ;

/* Variables and functions */
 int /*<<< orphan*/  CompartmentSourceVtbl ; 
 int /*<<< orphan*/  CompartmentVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Compartment_Constructor(CompartmentValue *valueData, ITfCompartment **ppOut)
{
    Compartment *This;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(Compartment));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITfCompartment_iface.lpVtbl= &CompartmentVtbl;
    This->ITfSource_iface.lpVtbl = &CompartmentSourceVtbl;
    This->refCount = 1;

    This->valueData = valueData;
    VariantInit(&This->variant);

    list_init(&This->CompartmentEventSink);

    *ppOut = &This->ITfCompartment_iface;
    TRACE("returning %p\n", *ppOut);
    return S_OK;
}