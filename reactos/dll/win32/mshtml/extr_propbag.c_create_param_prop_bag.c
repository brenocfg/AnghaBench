#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; TYPE_3__ IPropertyBag_iface; int /*<<< orphan*/  props; TYPE_1__ IPropertyBag2_iface; } ;
typedef  TYPE_2__ PropertyBag ;
typedef  TYPE_3__ IPropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPropertyBag_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  PropertyBag2Vtbl ; 
 int /*<<< orphan*/  PropertyBagVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  fill_props (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* heap_alloc (int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT create_param_prop_bag(nsIDOMHTMLElement *nselem, IPropertyBag **ret)
{
    PropertyBag *prop_bag;
    HRESULT hres;

    prop_bag = heap_alloc(sizeof(*prop_bag));
    if(!prop_bag)
        return E_OUTOFMEMORY;

    prop_bag->IPropertyBag_iface.lpVtbl  = &PropertyBagVtbl;
    prop_bag->IPropertyBag2_iface.lpVtbl = &PropertyBag2Vtbl;
    prop_bag->ref = 1;

    list_init(&prop_bag->props);
    hres = fill_props(nselem, prop_bag);
    if(FAILED(hres) || list_empty(&prop_bag->props)) {
        IPropertyBag_Release(&prop_bag->IPropertyBag_iface);
        *ret = NULL;
        return hres;
    }

    *ret = &prop_bag->IPropertyBag_iface;
    return S_OK;
}