#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_21__ {int /*<<< orphan*/ * vtbl; } ;
typedef  TYPE_7__ dispex_static_data_t ;
struct TYPE_18__ {int /*<<< orphan*/  dispex; } ;
struct TYPE_14__ {TYPE_6__* vtbl; int /*<<< orphan*/ * cp_container; int /*<<< orphan*/ * nsnode; TYPE_4__ event_target; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {TYPE_13__ node; TYPE_5__ IHTMLElement_iface; int /*<<< orphan*/  cp_container; int /*<<< orphan*/ * nselem; TYPE_3__ IHTMLElement4_iface; TYPE_2__ IHTMLElement3_iface; TYPE_1__ IHTMLElement2_iface; } ;
struct TYPE_20__ {int /*<<< orphan*/  cpc_entries; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_8__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainer_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLDOMNode_Init (int /*<<< orphan*/ *,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLElement2Vtbl ; 
 int /*<<< orphan*/  HTMLElement3Vtbl ; 
 int /*<<< orphan*/  HTMLElement4Vtbl ; 
 int /*<<< orphan*/  HTMLElementVtbl ; 
 TYPE_7__ HTMLElement_dispex ; 
 int /*<<< orphan*/  HTMLElement_dispex_vtbl ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 

void HTMLElement_Init(HTMLElement *This, HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, dispex_static_data_t *dispex_data)
{
    This->IHTMLElement_iface.lpVtbl = &HTMLElementVtbl;
    This->IHTMLElement2_iface.lpVtbl = &HTMLElement2Vtbl;
    This->IHTMLElement3_iface.lpVtbl = &HTMLElement3Vtbl;
    This->IHTMLElement4_iface.lpVtbl = &HTMLElement4Vtbl;

    if(dispex_data && !dispex_data->vtbl)
        dispex_data->vtbl = &HTMLElement_dispex_vtbl;
    init_dispex(&This->node.event_target.dispex, (IUnknown*)&This->IHTMLElement_iface,
            dispex_data ? dispex_data : &HTMLElement_dispex);

    if(nselem) {
        HTMLDOMNode_Init(doc, &This->node, (nsIDOMNode*)nselem);

        /* No AddRef, share reference with HTMLDOMNode */
        assert((nsIDOMNode*)nselem == This->node.nsnode);
        This->nselem = nselem;
    }

    This->node.cp_container = &This->cp_container;
    ConnectionPointContainer_Init(&This->cp_container, (IUnknown*)&This->IHTMLElement_iface, This->node.vtbl->cpc_entries);
}